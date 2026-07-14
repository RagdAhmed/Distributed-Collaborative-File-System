#ifndef NET_UTILS_H
#define NET_UTILS_H

#include <stddef.h>

int send_all(int sockfd, const void *buf, size_t len);
int recv_all(int sockfd, void *buf, size_t len);

#endif