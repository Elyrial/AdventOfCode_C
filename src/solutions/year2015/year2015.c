#include "year2015.h"
#include "day01.h"
#include <stddef.h>

static SolveFn days[] = {
    NULL,               /* day 0 unused */
    solve_2015_day01,   /* day 1 */
};

SolveFn
get_solution_2015(int day)
{
    if (day < 1 || (size_t)day >= sizeof(days) / sizeof(days[0]))
        return NULL;
    return days[day];
}
