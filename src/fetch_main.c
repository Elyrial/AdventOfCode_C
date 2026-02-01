#include "fetch_input.h"
#include "common.h"

#include <stdlib.h>

int
main(int argc, char **argv)
{
    load_dotenv_if_present(".env");

    if (argc != 3) {
        return 1;
    }

    return fetch_and_save_input(
        atoi(argv[1]),
        atoi(argv[2]),
        getenv("AOC_SESSION")
    );
}

