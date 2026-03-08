#include "runner.h"
#include "common.h"
#include "solutions/solutions.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int
runner_main(int argc, char **argv)
{
    if (argc < 4 || strcmp(argv[1], "run") != 0) {
        fprintf(stderr, "Usage: aoc run <year> <day>\n");
        return 1;
    }

    int year = atoi(argv[2]);
    int day = atoi(argv[3]);

    char path[256];
    snprintf(path, sizeof(path),
             "inputs/year%d/day%02d.txt", year, day);

    Buffer input;
    if (file_read_all(path, &input) != 0) {
        fprintf(stderr, "Failed to read input\n");
        return 1;
    }

    SolveFn fn = get_solution(year, day);
    if (fn == NULL) {
        fprintf(stderr, "No solution\n");
        return 1;
    }

    SolveResult r = fn(input.data);

    printf("Part 1 (%ld µs): %s\n", r.t1_us, r.part1);
    printf("Part 2 (%ld µs): %s\n", r.t2_us, r.part2);

    buffer_free(&input);

    return 0;
}

