

/*
 * Date:2021-12-06 10:26
 * filename:util.h
 *
 */

#ifndef UTIL
#define UTIL

#include <cstdlib>

ssize_t readn(int fd, void* buff, size_t n);
ssize_t writen(int fd, void* buff, size_t n);
void handle_for_sigpipe();
int setSocketNonBlocking(int fd);

#endif


