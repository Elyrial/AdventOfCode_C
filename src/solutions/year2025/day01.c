#include "day01.h"
#include "common.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static long long
part1(const char *input)
{
    long dial = 50;
    long long counter = 0;
    const char *p = input;

    while (*p) {
        char dir = *p;
        long value;

        p++;
        value = strtol(p, (char **)&p, 10);

        if (dir == 'L') {
            dial -= value;
        } else {
            dial += value;
        }

        dial = ((dial % 100) + 100) % 100;

        if (dial == 0) {
            counter++;
        }

        if (*p == '\n') {
            p++;
        }
    }

    return counter;
}

static long long
part2(const char *input)
{
    long dial = 50;
    long long counter = 0;
    const char *p = input;

    while (*p) {
        char dir = *p;
        long value;

        p++;
        value = strtol(p, (char **)&p, 10);

        if (dir == 'R') {
            counter += (dial + value) / 100;
            dial = ((dial + value) % 100 + 100) % 100;
        } else {
            long t = (dial == 0) ? 100 : dial;

            if (value >= t) {
                counter += 1 + (value - t) / 100;
            }

            dial = ((dial - value) % 100 + 100) % 100;
        }

        if (*p == '\n') {
            p++;
        }
    }

    return counter;
}

SolveResult
solve_2025_day01(const char *input)
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
