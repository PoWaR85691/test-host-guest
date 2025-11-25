#include "hostconnection.h"

#include <cstdio>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#include "common.h"

HostConnection::HostConnection(const std::string& address)
{
    m_fdSock = socket(AF_UNIX, SOCK_STREAM, 0);
    if (m_fdSock < 0) {
        perror("socket");
        return;
    }

    sockaddr_un addr;
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, address.c_str(), sizeof(addr.sun_path) - 1);

    if (connect(m_fdSock, reinterpret_cast<const struct sockaddr*>(&addr), sizeof(addr)) < 0) {
        perror("connect");
        return;
    }
}

HostConnection::~HostConnection()
{
    close(m_fdSock);
}

bool HostConnection::isValid() const
{
    return m_fdSock >= 0;
}

bool HostConnection::send(const Bytes& data)
{
    return sendToFd(m_fdSock, data);
}

std::pair<bool, Bytes> HostConnection::receive()
{
    return receiveFromFd(m_fdSock);
}