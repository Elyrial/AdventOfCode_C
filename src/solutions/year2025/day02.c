#include "day02.h"
#include "common.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int
is_repeated(unsigned long long n)
{
    char s[24];
    int len;
    int mid;
    int i;

    snprintf(s, sizeof(s), "%llu", n);
    len = (int)strlen(s);
    if (len % 2 != 0)
        return 0;

    mid = len / 2;
    for (i = 0; i < mid; i++) {
        if (s[i] != s[mid + i])
            return 0;
    }
    return 1;
}

static int
is_repeated_at_least_twice(unsigned long long n)
{
    char s[24];
    int len;
    int block_len;

    snprintf(s, sizeof(s), "%llu", n);
    len = (int)strlen(s);

    for (block_len = 1; block_len <= len / 2; block_len++) {
        int i;

        if (len % block_len != 0)
            continue;

        for (i = block_len; i < len; i += block_len) {
            if (memcmp(s, s + i, (size_t)block_len) != 0)
                goto next;
        }
        return 1;

next:;
    }
    return 0;
}

static long long
part1(const char *input)
{
    long long total = 0;
    const char *p = input;

    while (*p) {
        unsigned long long start, end, n;
        char *ep;

        start = strtoull(p, &ep, 10);
        if (*ep != '-')
            break;
        p = ep + 1;
        end = strtoull(p, &ep, 10);
        p = ep;

        for (n = start; n <= end; n++) {
            if (is_repeated(n))
                total += (long long)n;
        }

        if (*p == ',')
            p++;
        else if (*p == '\n' || *p == '\0')
            break;
    }

    return total;
}

static long long
part2(const char *input)
{
    long long total = 0;
    const char *p = input;

    while (*p) {
        unsigned long long start, end, n;
        char *ep;

        start = strtoull(p, &ep, 10);
        if (*ep != '-')
            break;
        p = ep + 1;
        end = strtoull(p, &ep, 10);
        p = ep;

        for (n = start; n <= end; n++) {
            if (is_repeated_at_least_twice(n))
                total += (long long)n;
        }

        if (*p == ',')
            p++;
        else if (*p == '\n' || *p == '\0')
            break;
    }

    return total;
}

SolveResult
solve_2025_day02(const char *input)
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
