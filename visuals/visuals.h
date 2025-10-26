#ifndef VISUALS_H
#define VISUALS_H

#include "../helper/functions.h"

#include <termios.h>  // terminal input
#include <fcntl.h>
#include <errno.h>

void visuals();
void child();
void parent(pid_t& pid);




#endif
