#ifndef __UTILS_H
#define __UTILS_H

#include <stdlib.h>
#include <signal.h>
#include <ncursesw/curses.h>
#include <sys/time.h>

void grace_shutdown(int id);
void register_grace_shutdowns();
long long timeInMilliseconds();

#endif