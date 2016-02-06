#ifndef _CARAVAN_IO_H
#define _CARAVAN_IO_H

struct caravan_io_ops {
    int (*exists)(void * state, const char * path);
    char * (*cwd)(void * state, char * buf, unsigned int bufsize);
    void (*state_free)(void * state); /* free any state */
};

struct caravan_io {
    void * state;
    struct caravan_io_ops ops;
};

struct caravan_io * caravan_io_init(struct caravan_io * io, void * state, struct caravan_io_ops ops);
int caravan_io_exists(struct caravan_io * io, const char * path);
char * caravan_io_cwd(struct caravan_io * io, char * buf, unsigned int bufsize);
struct caravan_io * caravan_io_free(struct caravan_io * io);

#endif
