#!/bin/bash

# directories
src_dir="../src"
inc_dir="../inc"
build_dir="../build"
error_log="error_log.txt"

# create build directory, if it doesn't exist
mkdir -p "$build_dir"

files=(
  "publisher.cpp"
  "subscriber.cpp"
  "broker.cpp"
)

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

  for (( i=0; i<num_chars; i++ )); do
    bar+="="
  done

  printf "[%-*s] %d%%\r" "$bar_length" "$bar" "$(( (progress * 100) / total_files ))"
}

# compile files
total_files=${#files[@]}
completed_files=0

for file in "${files[@]}"; do
  ((completed_files++))
  show_progress_bar "$completed_files"

  g++ -c "$src_dir/$file" -I"$inc_dir" -o "$build_dir/${file%.*}.o" >> "$error_log" 2>&1
  if [ $? -ne 0 ]; then
    echo -e "\nError compiling file: $file"
    exit 1
  fi

  g++ "$build_dir/${file%.*}.o" -o "$build_dir/${file%.*}_executable" >> "$error_log" 2>&1
  if [ $? -ne 0 ]; then
    echo -e "\nError creating executable for file: $file"
    exit 1
  fi

  compiled_files+=("$file")
done

echo -e "\nCompilation successful"

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
