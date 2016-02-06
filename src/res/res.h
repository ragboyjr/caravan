#ifndef _CARAVAN_RES_H
#define _CARAVAN_RES_H

struct caravan_res {
    struct caravan_io * io;
    int (*system)(const char *);
    char * project_path;
};

struct caravan_res * caravan_res_init(struct caravan_res * res, struct caravan_io * io);
struct caravan_res * caravan_res_init_raw(struct caravan_res * res, struct caravan_io * io, int (*system)(const char *));
struct caravan_res * caravan_res_free(struct caravan_res * res);

/** ran man locally to the caravan deps path */
void caravan_res_man(struct caravan_res * res, const char * arg);

#endif
