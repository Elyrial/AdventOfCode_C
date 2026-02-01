#ifndef AOC_SOLUTIONS_H
#define AOC_SOLUTIONS_H

typedef struct {
    char *part1;
    char *part2;
    long t1_us;
    long t2_us;
} SolveResult;

typedef SolveResult (*SolveFn)(const char *input);

SolveFn get_solution(int year, int day);

#endif

