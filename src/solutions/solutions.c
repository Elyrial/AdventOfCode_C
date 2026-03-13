#include "solutions.h"
#include "year2015/year2015.h"
#include "year2025/year2025.h"
#include <stddef.h>

typedef struct {
    int year;
    SolveFn (*get)(int);
} YearEntry;

static YearEntry years[] = {
    { 2015, get_solution_2015 },
    { 2025, get_solution_2025 },
};

SolveFn
get_solution(int year, int day)
{
    for (size_t i = 0; i < sizeof(years) / sizeof(years[0]); i++) {
        if (years[i].year == year)
            return years[i].get(day);
    }
    return NULL;
}
