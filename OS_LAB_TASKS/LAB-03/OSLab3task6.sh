#!/bin/bash

TARGET_DIR="/home/student/Source"

find "$TARGET_DIR" -type f -empty -delete

echo "All empty files in $TARGET_DIR have been deleted."

