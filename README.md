# AdventOfCode_C

Advent of Code solutions written in C, with a small framework for fetching inputs and timing each part.

## Requirements

- CMake 3.16+
- A C11 compiler (GCC or Clang)
- libcurl (for fetching puzzle inputs)

## Build

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

This produces two binaries in `build/`:

| Binary | Purpose |
|---|---|
| `aoc` | Run a solution |
| `fetch_input` | Download a puzzle input from adventofcode.com |

## Running a solution

```sh
./run.sh <year> <day>
```

`run.sh` fetches the input automatically if it is not already present, then runs the solution. The build directory defaults to `./build` and can be overridden:

```sh
BUILD_DIR=/path/to/build ./run.sh 2025 1
```

To run directly:

```sh
./build/aoc run 2025 1
```

## Fetching inputs manually

Create a `.env` file in the project root with your session cookie:

```
AOC_SESSION=your_session_cookie_here
```

Then:

```sh
./build/fetch_input 2025 1
```

Inputs are saved to `inputs/year<YYYY>/day<DD>.txt`.

## Adding a new solution

1. Create `src/solutions/year<YYYY>/day<DD>.c` and `day<DD>.h` following the pattern in `year2025/day01.*`.
2. Register the function in `src/solutions/year<YYYY>/year<YYYY>.c` by appending it to the `days[]` array.
3. Re-run CMake (the build system picks up new `.c` files via `GLOB_RECURSE` automatically after reconfiguring).

To add a new year, create `year<YYYY>.c`/`year<YYYY>.h` and add an entry to the `years[]` table in `src/solutions/solutions.c`.

## Project structure

```
src/
  common.c/h          — shared utilities (I/O, timing, string helpers)
  main.c              — entry point
  runner.c/h          — CLI argument parsing and solution dispatch
  fetch_input.c/h     — input downloader (libcurl)
  fetch_main.c        — entry point for fetch_input binary
  solutions/
    solutions.c/h     — year dispatch table
    year2025/
      year2025.c/h    — day dispatch table for 2025
      day01.c/h       — solution for day 1
inputs/
  year2025/
    day01.txt         — puzzle inputs (not tracked in git)
```
