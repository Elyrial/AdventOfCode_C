#include "day01.h"
#include "common.h"

static long long
part1(const char *input)
{
    long long floor = 0;
    const char *p = input;

    while (*p) {
        if (*p == '(')
            floor++;
        else if (*p == ')')
            floor--;
        p++;
    }

    return floor;
}

static long long
part2(const char *input)
{
    long long floor = 0;
    const char *p = input;

    while (*p) {
        if (*p == '(')
            floor++;
        else if (*p == ')')
            floor--;
        if (floor == -1)
            return (long long)(p - input) + 1;
        p++;
    }

    return -1;
}

SolveResult
solve_2015_day01(const char *input)
{
    SolveResult r = {0};
    long t0;

    t0 = now_micros();
    ll_to_str(part1(input), r.part1, sizeof(r.part1));
    r.t1_us = now_micros() - t0;

    t0 = now_micros();
    ll_to_str(part2(input), r.part2, sizeof(r.part2));
    r.t2_us = now_micros() - t0;

    return r;
}
