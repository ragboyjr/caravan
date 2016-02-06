#include "io.h"
#include <assert.h>

struct caravan_io * caravan_io_init(struct caravan_io * io, void * state, struct caravan_io_ops ops) {
    assert(io);
    io->state = state;
    io->ops = ops;

    return io;
}
int caravan_io_exists(struct caravan_io * io, const char * path) {
    assert(io);
    return io->ops.exists(io->state, path);
}
char * caravan_io_cwd(struct caravan_io * io, char * buf, unsigned int bufsize) {
    assert(io);
    return io->ops.cwd(io->state, buf, bufsize);
}
struct caravan_io * caravan_io_free(struct caravan_io * io) {
    assert(io);
    io->ops.state_free(io->state);
    return io;
}
