#include "utils.h"

void grace_shutdown(int id) {
    endwin();
    exit(1);
}

void register_grace_shutdowns() {
    signal(SIGABRT, grace_shutdown);
    signal(SIGFPE, grace_shutdown);
    signal(SIGILL, grace_shutdown);
    signal(SIGINT, grace_shutdown);
    signal(SIGSEGV, grace_shutdown);
    signal(SIGTERM, grace_shutdown);
}

long long timeInMilliseconds() {
    struct timeval tv;

    gettimeofday(&tv,NULL);
    return (((long long)tv.tv_sec)*1000)+(tv.tv_usec/1000);
}