#!/bin/bash

TARGET_DIR="/home/student/Source_folder"

find "$TARGET_DIR" -type f -exec ls -lhS {} + | awk '{ print $9 ": " $5 }'

