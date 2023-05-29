#!/bin/bash

# change to scripts directory if not already in it
current_dir=$(basename "$PWD")
scripts_dir="scripts"

if [ "$current_dir" != "$scripts_dir" ]; then
  cd "$scripts_dir" || exit 1
fi

# directories
src_dir="../tests"
build_dir="../build"
error_log="unit_test_error_log.txt"

# include paths
include_paths=(
  "-I../inc"
  "-I../inc/global"
  "-I../src"
  "-I../lib"
)

# compiler flags
cpp_standard="-std=c++11"
cpp_flags=(
  "$cpp_standard"
  "-Wall"
  "-Wextra"
  "-O2"
)

# create build directory, if it doesn't exist
mkdir -p "$build_dir"

# global variables and arrays
files=()            # array for sourcefiles
compiled_files=()   # array to store compiled files
total_files=0
completed_files=0

# get all files from test folder and store them in the array
while IFS= read -r -d '' file; do
  files+=("${file#$src_dir}")
  ((total_files++))
done < <(find "$src_dir" -type f -name "*.cpp" -print0)

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

remove_object_files() {
  rm "$build_dir"/*.o >> "$error_log" 2>&1
}

# compile files
clear

for file in "${files[@]}"; do
  prev_compiled_files="$completed_files"
  ((completed_files++))
  show_progress_bar "$completed_files" "$prev_compiled_files"

  g++ -c "$src_dir/$file" ${include_paths[@]} ${cpp_flags[@]} -o "$build_dir/${file%.*}.o" >> "$error_log" 2>&1
  if [ $? -ne 0 ]; then
    tput setaf 1
    echo -e "\nError compiling file: $file"
    tput sgr0
    print_error_log
    remove_object_files
    exit 1
  fi

  g++ "$build_dir/${file%.*}.o" ${cpp_flags[@]} -o "$build_dir/${file%.*}_executable" >> "$error_log" 2>&1
  if [ $? -ne 0 ]; then
    tput setaf 1
    echo -e "\nError creating executable for file: $file"
    tput sgr0
    print_error_log
    remove_object_files
    exit 1
  fi

  compiled_files+=("$file")
done

tput setaf 10
echo -e "\nCompilation successful"
tput sgr0

# display compiled files
echo -e "\nCompiled files:"
for compiled_file in "${compiled_files[@]}"; do
  echo "- ${compiled_file#/}"
done

remove_object_files

# delete error log file if there are no errors
if [ ! -s "$error_log" ]; then
  rm "$error_log"
fi
