#!/bin/bash


if [ $# -ne 1 ]; then
    echo "Usage: $0 <input_string>"
    exit 1
fi

input_string="$1"

length=${#input_string}

if [ "$length" -eq 1 ]; then
    mpic++ -o program vuv.cpp
    mpirun -np 1 ./program "$input_string"
else
    num_edges=$((2 * (length - 1)))

    mpic++ -o program vuv.cpp
    mpirun -np "$num_edges" ./program "$input_string"
fi