#include "solutions.h"
#include "year2025/year2025.h"
#include <stddef.h>

SolveFn
get_solution(int year, int day)
{
    if (year == 2025) {
        return get_solution_2025(day);
    }
    return NULL;
}

