#include "path.h"

#include <assert.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>

static int has_deps(struct caravan_io * io, char * buf, const char * path) {
    buf[0] = '\0';
    strcat(buf, path);
    strcat(buf, "/caravan_deps");

    return caravan_io_exists(io, buf);
}

char * caravan_res_path_deps_find(struct caravan_io * io, char * buf, size_t size) {
    int buflen = 0;
    char * deps_buf;

    buf = caravan_io_cwd(io, buf, size);
    if (!buf) {
        return buf;
    }

    buflen = strlen(buf);
    deps_buf = malloc(buflen + strlen("/caravan_deps") + 1);

    /* look for the caravan_deps, and then back off until we find it */
    while (*buf && !has_deps(io, deps_buf, buf)) {
        char * p = rindex(buf, '/');
        buf[p - buf] = '\0'; /* back off */
    }

    free(deps_buf);

    if (!*buf) {
        return NULL; /* it wasn't found */
    }

    return buf;
}
