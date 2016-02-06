#ifndef _CARAVAN_RES_PATH_H
#define _CARAVAN_RES_PATH_H

#include "../io/io.h"
#include <stdlib.h>

/** finds the caravan deps path by searching for the closest caravan_deps directory */
char * caravan_res_path_deps_find(struct caravan_io * io, char * buf, size_t bufsize);

#endif
