#!/bin/bash

# change to scripts directory if not already in it
current_dir=$(basename "$PWD")
scripts_dir="scripts"

if [ "$current_dir" != "$scripts_dir" ]; then
  cd "$scripts_dir" || exit 1
fi

# directories
src_dir="../src"
lib_dir="../lib"
build_dir="../build"
lib_build_dir="../build/lib"

# files
error_log="error_log.txt"

lib_std="lib_std.a"
lib_std_ld="${lib_std#lib}"
lib_std_ld="${lib_std_ld%.*}"

# include paths
include_paths=(
  "-I../inc"
  "-I../inc/global"
  "-I../lib"
  "-I../lib/biglib"
)

# compiler flags
cpp_standard="-std=c++11"
cpp_flags=(
  "$cpp_standard"
  "-Wall"
  "-Wextra"
  "-O2"
)

# create build directories
mkdir -p "$build_dir"
mkdir -p "$lib_build_dir"

# support colors
tput init

# variables / arrays
files=()              # array for sourcefiles
lib_files=()          # array for library files
compiled_files=()     # array to store compiled files

# get all files from src folder and store them in the array
while IFS= read -r -d '' file; do
  files+=("${file#$src_dir}")
done < <(find "$src_dir" -type f -name "*.cpp" -print0)

# get all files from lib folder and store them in the array
while IFS= read -r -d '' file; do
  lib_files+=("${file#$lib_dir}")
done < <(find "$lib_dir" -type f -name "*.cpp" -print0)

while getopts ":pbsr" opt; do
  case $opt in
    p)
      files=(
        "publisher.cpp"
      )
      ;;
    b)
      files=(
        "broker.cpp"
      )
      ;;
    s)
      files=(
        "subscriber.cpp"
      )
      ;;
    \?)
      echo "invalid option: -$OPTARG" >&2
      exit 1
      ;;
  esac
done

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

print_error_log() {
  if [ -s "$error_log" ]; then
    echo -e "\n\n------------------------------"
    tput setaf 9
    echo -e "Errors:\n"
    tput sgr0
    cat "$error_log"
  fi
}

clean_up() {
  local dir="$1"
  rm "$dir"/*.o >> "$error_log" 2>&1
}

# create or update library
for lib_file in "${lib_files[@]}"; do
  g++ -c "$lib_dir/$lib_file" ${include_paths[@]} ${cpp_flags[@]} -o "$lib_build_dir/${lib_file%.*}.o" >> "$error_log" 2>&1
  if [ $? -ne 0 ]; then
    tput setab 0
    tput setaf 1
    echo -e "\nError compiling library file: $lib_file"
    tput sgr0
    print_error_log
    clean_up "$lib_build_dir"
    exit 1
  fi
done

ar rcs "$lib_build_dir/$lib_std" "$lib_build_dir"/*.o >> "$error_log" 2>&1
if [ $? -ne 0 ]; then
  tput setab 0
  tput setaf 1
  echo -e "\nError creating library"
  tput sgr0
  print_error_log
  clean_up "$lib_build_dir"
  exit 1
fi

# clean up build folder
clean_up "$lib_build_dir"


# compile files
total_files=${#files[@]}
completed_files=0
clear

for file in "${files[@]}"; do
  prev_compiled_files="$completed_files"
  ((completed_files++))
  show_progress_bar "$completed_files" "$prev_compiled_files"

  g++ -c "$src_dir/$file" ${include_paths[@]} ${cpp_flags[@]} -o "$build_dir/${file%.*}.o" >> "$error_log" 2>&1
  if [ $? -ne 0 ]; then
    tput setab 0
    tput setaf 1
    echo -e "\nError compiling file: $file"
    tput sgr0
    print_error_log
    clean_up "$build_dir"
    exit 1
  fi

  g++ "$build_dir/${file%.*}.o" -L${lib_build_dir} -l${lib_std_ld} ${cpp_flags[@]} -o "$build_dir/${file%.*}_exe" -v >> "$error_log" 2>&1
  if [ $? -ne 0 ]; then
    tput setab 0
    tput setaf 1
    echo -e "\nError creating executable for file: $file"
    tput sgr0
    print_error_log
    clean_up "$build_dir"
    exit 1
  fi

  compiled_files+=("$file")
done

clean_up "$build_dir"

tput setab 0
tput setaf 2
echo -e "\nCompilation successful"
tput sgr0

# display compiled files
tput setaf 3
echo -e "\nCompiled files:"
tput sgr0
for compiled_file in "${compiled_files[@]}"; do
  echo "- ${compiled_file#/}"
done

# delete error log file if there are no errors
if [ ! -s "$error_log" ]; then
  rm "$error_log"
fi
