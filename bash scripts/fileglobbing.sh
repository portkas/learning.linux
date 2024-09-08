#!/usr/bin/bash

echo "ignore fileglobbing option turned off"
ls *

echo "ignore file globbing option set"
set -f
ls *
set +f

