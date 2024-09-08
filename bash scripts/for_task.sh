#!/bin/bash

function itemname1 {
	for item in *; do
    if [ -f "$item" ]; then
			echo "$item is $(echo ${#item})"
		elif [ -d "$item" ]; then
			echo "$item has $(echo ${#item})"
		fi
	done
}

function itemname2 {
	for item in *; do
		echo "$item has $(echo "$item" | wc -c)"
	done
}

itemname2
