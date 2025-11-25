#ifndef COMMON_H
#define COMMON_H

#include "baseconnection.h"

bool sendToFd(int fd, const Bytes& data);
std::pair<bool, Bytes> receiveFromFd(int fd);

#endif