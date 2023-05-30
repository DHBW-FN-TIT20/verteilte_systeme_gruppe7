#!/bin/bash

# change to scripts directory if not already in it
current_dir=$(basename "$PWD")
scripts_dir="scripts"

if [ "$current_dir" != "$scripts_dir" ]; then
  cd "$scripts_dir" || exit 1
fi

# directories
build_dir="../build"

# support colors
tput init

# array to store executable files
for file in "$build_dir"/test_*; do
  if [ -f "$file" ]; then
    files+=("$file")
  fi
done

# check whether there are test files in the build directory
if [ ${#files[@]} -eq 0 ]; then
  tput setaf 9
  echo -e "\nNo executable files found in $build_dir"
  tput sgr0
  exit 1
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

run_executables() {
  local files=("$@")
  local total_files=${#files[@]}
  local completed_files=0

  for file in "${files[@]}"; do
    prev_executed_files="$completed_files"
    ((completed_files++))
    clear
    show_progress_bar "$completed_files" "$prev_executed_files"

    echo -e "\n"
    "./$file" 2>&1
    if [ $? -ne 0 ]; then
      tput setaf 1
      echo -e "\nTest failed in file: $file"
      tput sgr0
      exit 1
    fi
    sleep 0.05
  done
  echo -e "\n\n----------------"
  tput setaf 10
  echo -e "Tests successful"
  tput sgr0
}

run_executables "${files[@]}"

# display copmiled files
echo -e "\nExecuted tests:"
for file in "${files[@]}"; do
  output="${file#$build_dir}"
  output="${output#/}"
  echo "- $output"
done
