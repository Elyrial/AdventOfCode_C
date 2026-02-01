#!/usr/bin/env bash
set -euo pipefail

if [ "$#" -ne 2 ]; then
    echo "Usage: $0 <year> <day>"
    exit 1
fi

year="$1"
day="$2"
padded_day=$(printf "%02d" "$day")

input_file="inputs/year${year}/day${padded_day}.txt"

if [ ! -f "$input_file" ]; then
    echo "Input file not found, fetching..."
    ./build/fetch_input "$year" "$day"
fi

./build/aoc run "$year" "$day"

