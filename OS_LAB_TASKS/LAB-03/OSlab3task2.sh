#!/bin/bash
compress_dir(){
local dir=$*
if [ ! -d "$dir" ]; then
	echo "Error: $dir doesnot exist."
	exit 1
fi

local curr_date=$(date '+%d-%m-%Y_%H-%M-%S')
if tar czf "./$dir ($curr_date).tar.gz" $dir; then
	echo "$dir directory compressed successfully!"
else
	echo "Error: Couldnot compress $dir directory"
fi
}

extract_archive(){
local archive_name=$1
if [ ! -e "$archive_name" ]; then
	echo "ERror: $archive_name doesnot exist."
	exit 1
fi

if tar xzf $archive_name &> /dev/null; then
	echo "$archive_name archive extracted successfully!"
else
	echo "Error: Couldnot extract $archive_name archive."
fi
}
