#ifndef VISUALS_H
#define VISUALS_H

#include "../helper/functions.h"

#include <sys/wait.h>   // waitpid()
#include <signal.h>     // kill(), SIGTERM


void visuals();
void child();
int parent(pid_t& pid);



void donut();





#endif