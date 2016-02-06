#include "unix.h"
#include <unistd.h>
#include <assert.h>

static int unix_exists(void * state, const char * path) {
    return access(path, F_OK) == 0;
}

static char * unix_cwd(void * state, char * buf, unsigned int bufsize) {
    return getcwd(buf, bufsize);
}

static void unix_free(void * state) {
    /* no op */
}

struct caravan_io * caravan_io_init_unix(struct caravan_io * io) {
    assert(io);
    struct caravan_io_ops ops = {
        unix_exists,
        unix_cwd,
        unix_free
    };

    io->state = NULL;
    io->ops = ops;

    return io;
}
