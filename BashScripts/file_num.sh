#!/usr/bin/bash

user=$(whoami)
input=/home/$user/Desktop

function total_files {
	find $1 -type f | wc -l
}

function total_directories {
	find $1 -type d | wc -l
}

echo -n "Files to be included:"
total_files $input
echo -n  "Directories to be included:"
total_directories $input
