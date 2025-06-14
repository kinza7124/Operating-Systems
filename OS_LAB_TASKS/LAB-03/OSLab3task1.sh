#!/bin/bash

SOURCE_FOLDER="/home/student/Source"

mkdir -p "$SOURCE_FOLDER/Images" "$SOURCE_FOLDER/Documents" "$SOURCE_FOLDER/Others"

for file in "$SOURCE_FOLDER"/*; do
    if [ -f "$file" ]; then
        extension="${file##*.}"
        case "$extension" in
            jpg|jpeg|png|gif)
                mv "$file" "$SOURCE_FOLDER/Images/"
                ;;
            txt|doc|docx|pdf)
                mv "$file" "$SOURCE_FOLDER/Documents/"
                ;;
            *)
                mv "$file" "$SOURCE_FOLDER/Others/"
                ;;
        esac
    fi
done

echo "Files have been sorted."

