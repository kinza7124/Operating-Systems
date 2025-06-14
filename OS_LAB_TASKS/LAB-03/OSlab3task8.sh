#!/bin/bash
if [ "$#" -ne 2 ]; then
    echo "Usage: $0 <directory_path> <new_file_name_pattern>"
    exit 1
fi

dir_path="$1"
new_pattern="$2"

if [ ! -d "$dir_path" ]; then
    echo "Error: Directory '$dir_path' not found."
    exit 1
fi

count=1

for file in "$dir_path"/*; do
    if [ -f "$file" ]; then
        ext="${file##*.}" 
        new_name="${new_pattern}${count}.${ext}"
        new_path="$dir_path/$new_name"
        
        mv "$file" "$new_path"
        if [ $? -eq 0 ]; then
            echo "Renamed '$file' to '$new_path'"
        else
            echo "Error renaming '$file'"
        fi
        
        ((count++))
    fi
done

echo "Renaming process completed."

