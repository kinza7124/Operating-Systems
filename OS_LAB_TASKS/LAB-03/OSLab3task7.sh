#!/bin/bash

SOURCE_DIR="/home/student/Source_folder"

DEST_DIR="/home/student/Dest_folder"

mkdir -p "$DEST_DIR"

cp "$SOURCE_DIR"/*.txt "$DEST_DIR"

echo "All .txt files have been copied from $SOURCE_DIR to $DEST_DIR"

