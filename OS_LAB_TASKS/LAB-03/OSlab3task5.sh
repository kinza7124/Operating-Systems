#!/bin/bash

backup_folder="backup"

if [ ! -d "$backup_folder" ]; then
    mkdir "$backup_folder"
    echo "Created backup folder: $backup_folder"
fi

find . -maxdepth 1 -type f -mtime +7 -exec mv {} "$backup_folder" \;

if [ $? -eq 0 ]; then
    echo "Moved files older than 7 days to '$backup_folder'"
else
    echo "No files older than 7 days found."
fi

