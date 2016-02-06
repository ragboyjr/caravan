#include "res.h"
#include "path.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define PROJECT_PATH_LEN 255

struct caravan_res * caravan_res_init(struct caravan_res * res, struct caravan_io * io) {
    return caravan_res_init_raw(res, io, system);
}

struct caravan_res * caravan_res_init_raw(struct caravan_res * res, struct caravan_io * io, int (*system)(const char *)) {
    assert(res);
    assert(io);
    assert(system);

    res->io = io;
    res->system = system;
    res->project_path = malloc(sizeof(char) * PROJECT_PATH_LEN);
    res->project_path = caravan_res_path_deps_find(io, res->project_path, PROJECT_PATH_LEN);

    if (!res->project_path) {
        free(res->project_path);
        return NULL;
    }

    return res;
}

struct caravan_res * caravan_res_free(struct caravan_res * res) {
    free(res->project_path);
    return res;
}

/** ran man locally to the caravan deps path */
void caravan_res_man(struct caravan_res * res, const char * arg) {
    char buf[512];
    snprintf(buf, 512, "man -M %s/caravan_deps/share/man %s", res->project_path, arg);
    res->system(buf);
}
