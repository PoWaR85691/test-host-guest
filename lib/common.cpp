#include "common.h"
#include <unistd.h>
#include <cstdio>

bool sendToFd(int fd, const Bytes& data)
{
    size_t size = data.size();

    if (write(fd, &size, sizeof(size)) < 0) {
        perror("write size");
        return false;
    }

    if (write(fd, data.data(), size) < 0) {
        perror("write data");
        return false;
    }

    // The final character must be sent so that the guest machine driver can read the data
    char end = '\n';
    if (write(fd, &end, sizeof(end)) < 0) {
        perror("write end");
        return false;
    }

    return true;
}

std::pair<bool, Bytes> receiveFromFd(int fd)
{
    size_t size = 0;
    Bytes data;

    if (read(fd, &size, sizeof(size)) < 0) {
        perror("read size");
        return { false, Bytes() };
    }

    data.resize(size, 0);
    if (read(fd, data.data(), size) < 0) {
        perror("read data");
        return { false, Bytes() };
    }

    char end = '\0';
    if (read(fd, &end, sizeof(end)) < 0) {
        perror("read end");
        return { false, Bytes() };
    }

    return { true, data };
}