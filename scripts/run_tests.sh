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

run_executables() {
  local files=("$@")
  local total_files=${#files[@]}
  local completed_files=0

  for file in "${files[@]}"; do
    ((completed_files++))
    clear
    show_progress_bar "$completed_files"

    printf "\n\r%s " "$(./"$file" 2>&1)"
    if [ $? -ne 0 ]; then
      tput setaf 1
      echo -e "\nTest failed in file: $file"
      tput sgr0
      exit 1
    fi
    sleep 0.3
  done
  echo -e "\n\n----------------"
  tput setaf 2
  echo -e "\nTests successful"
  tput sgr0
}

executable_files=("$build_dir"/*)
if [ ${#executable_files[@]} -eq 0 ]; then
  tput setaf 1
  echo -e "\nNo executable files found in $build_dir"
  tput sgr0
  exit 1
fi

run_executables "${executable_files[@]}"

# display copmiled files
echo -e "\nExecuted tests:"
for executable_file in "${executable_files[@]}"; do
  echo "- $executable_file"
done
