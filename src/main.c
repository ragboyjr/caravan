#include <stdio.h>
#include "io/io.h"
#include "io/unix.h"
#include "res/res.h"

int main() {
    struct caravan_io io; caravan_io_init_unix(&io);
    struct caravan_res res;

    if (!caravan_res_init(&res, &io)) {
        printf("Project path could not be found!\n");
        return 1;
    }

    caravan_res_man(&res, "checkmk");

    caravan_res_free(&res);
    caravan_io_free(&io);

    return 0;
}
