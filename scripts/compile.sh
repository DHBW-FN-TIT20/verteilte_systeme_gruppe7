#!/bin/bash

# change to scripts directory if not already in it
current_dir=$(basename "$PWD")
scripts_dir="scripts"

if [ "$current_dir" != "$scripts_dir" ]; then
  cd "$scripts_dir" || exit 1
fi

# directories
src_dir="../src"
inc_dir="../inc"
build_dir="../build"
error_log="error_log.txt"

# create build directory, if it doesn't exist
mkdir -p "$build_dir"

# support colors
tput init

files=(
  "publisher.cpp"
  "subscriber.cpp"
  "broker.cpp"
  "message_parser.cpp"
)

while getopts ":pbs" opt; do
  case $opt in
    p)
      files=(
        "publisher.cpp"
        "message_parser.cpp"
      )
      ;;
    b)
      files=(
        "broker.cpp"
        "message_parser.cpp"
      )
      ;;
    s)
      files=(
        "subscriber.cpp"
        "message_parser.cpp"
      )
      ;;
    \?)
      echo "invalid option: -$OPTARG" >&2
      exit 1
      ;;
  esac
done

# array to store compiled files
compiled_files=()

# reset error log file
if [ -f "$error_log" ]; then
  > "$error_log"
fi

# function to print progress bar
show_progress_bar() {
  local progress="$1"
  local terminal_width=$(tput cols)
  local bar_length=$((terminal_width - 8))
  local num_chars=$(( (progress * bar_length) / total_files ))
  local bar=""

  local prev_progress="$2"
  local prev_num_chars=$(( (prev_progress * bar_length) / total_files ))
  #local prev_bar_length=$((num_chars - prev_num_chars))

  for (( i=0; i<prev_num_chars; i++ )); do
    bar+="="
  done
  printf "[%-*s] %d%%\r" "$bar_length" "$bar" "$(( (progress * 100) / total_files ))"

  for (( i=prev_num_chars; i<num_chars; i++ )); do
    bar+="="
    printf "[%-*s] %d%%\r" "$bar_length" "$bar" "$(( (progress * 100) / total_files ))"
    sleep 0.005
  done

}

# compile files
total_files=${#files[@]}
completed_files=0
clear

for file in "${files[@]}"; do
  prev_compiled_files="$completed_files"
  ((completed_files++))
  show_progress_bar "$completed_files" "$prev_compiled_files"

  g++ -c "$src_dir/$file" -I"$inc_dir" -o "$build_dir/${file%.*}.o" >> "$error_log" 2>&1
  if [ $? -ne 0 ]; then
    tput setaf 1
    echo -e "\nError compiling file: $file"
    tput sgr0
    exit 1
  fi

  g++ "$build_dir/${file%.*}.o" -o "$build_dir/${file%.*}_executable" >> "$error_log" 2>&1
  if [ $? -ne 0 ]; then
    tput setaf 1
    echo -e "\nError creating executable for file: $file"
    tput sgr0
    exit 1
  fi

  compiled_files+=("$file")
done

tput setaf 2
echo -e "\nCompilation successful"
tput sgr0

# display compiled files
echo -e "\nCompiled files:"
for compiled_file in "${compiled_files[@]}"; do
  echo "- $compiled_file"
done

# remove .o files
rm "$build_dir"/*.o

# delete error log file if there are no errors
if [ ! -s "$error_log" ]; then
  rm "$error_log"
fi
