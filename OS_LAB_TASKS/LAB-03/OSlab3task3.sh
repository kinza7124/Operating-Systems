#!/bin/bash
if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <filename>"
    exit 1
fi

filename="$1"

if [ ! -f "$filename" ]; then
    echo "Error: File '$filename' not found."
    exit 1
fi

base_name="${filename%.*}"
ext="${filename##*.}"

date_suffix="$(date +%Y-%m-%d)"

backup_file="${base_name}_${date_suffix}.${ext}"

cp "$filename" "$backup_file"

if [ $? -eq 0 ]; then
    echo "Backup created: '$backup_file'"
else
    echo "Error creating backup."
fi

