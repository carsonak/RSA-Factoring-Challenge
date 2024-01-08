#!/bin/bash

program_path="$1" # Program to run
tests_dir="./tests/factorising/" # Arguments to the program
out_dir="./" # Directory for the output directories

#Strip trailing slashes
strip_tslash(){
    if [[ "$1" = *"/" ]]; then
        echo "${1%/}"
    else
        echo "$1"
    fi
}

# Confirm directories exist
check_dir(){
    if [[ $# -ge 1 ]]; then
        for dir in "$@"; do
            if [[ -d "$dir" ]]; then
                :
            else
                printf "Invalid directory: %s\n" "$dir" >&2
                return 1
            fi
        done
    else
        echo "Not enough arguments" >&2
        return 1
    fi

    return 0
}

tests_dir=$(strip_tslash "$tests_dir")
out_dir=$(strip_tslash "$out_dir")

if check_dir "$tests_dir" "$out_dir" && [[ -r "$tests_dir" && -w "$out_dir" ]]; then
    # Iterate through all files in the directory
    for file in "$tests_dir/"*; do
        out_file="$out_dir/out_$(basename "$file" ".*").txt"
        # Time the program, terminate after 5 seconds, store its output in file
        time timeout -s TERM --preserve-status 4.99 "$program_path" "$file" > "$out_file"
        echo "Status: $?"
        wc -l "$out_file"
    done
fi
