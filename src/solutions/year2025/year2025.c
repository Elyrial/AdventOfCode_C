#include "year2025.h"
#include "day01.h"
#include <stddef.h>

SolveFn
get_solution_2025(int day)
{
    if (day == 1) {
        return solve_2025_day01;
    }
    return NULL;
}

