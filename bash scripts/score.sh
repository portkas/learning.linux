#!/usr/bin/bash

trap 'echo "line ${LINENO}: score is $score"' DEBUG

score=0

if [ "${USER}" = "mike" ]; then
	let "score += 1"
fi

let "score += 1"

if [ "$1" = "7" ]; then
	score=7
fi
exit 0

