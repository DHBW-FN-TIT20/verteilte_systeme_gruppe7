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

# create build directory, if it doesn't exist
mkdir -p "$build_dir"

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
total_files=0
completed_files=0
clear

while IFS= read -r -d '' file; do
  ((total_files++))
done < <(find "$src_dir" -type f -name "*.cpp" -print0)

while IFS= read -r -d '' file; do
  ((completed_files++))
  show_progress_bar "$completed_files"

  g++ -c "$file" -o "$build_dir/$(basename "${file%.*}").o" -std=c++11 >> "$error_log" 2>&1
  if [ $? -ne 0 ]; then
    tput setaf 1
    echo -e "\nError compiling file: $file"
    tput sgr0
    exit 1
  fi

  g++ "$build_dir/$(basename "${file%.*}").o" -o "$build_dir/$(basename "${file%.*}")_executable" -std=c++11 >> "$error_log" 2>&1
  if [ $? -ne 0 ]; then
    tput setaf 1
    echo -e "\nError creating executable for file: $file"
    tput sgr0
    exit 1
  fi

  compiled_files+=("$file")
done < <(find "$src_dir" -type f -name "*.cpp" -print0)

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
