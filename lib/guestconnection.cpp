#include "guestconnection.h"

#include <fcntl.h>
#include <unistd.h>

#include "common.h"

GuestConnection::GuestConnection(const std::string& address)
{
    m_address = address;
}

bool GuestConnection::isValid() const
{
    return access(m_address.c_str(), R_OK | W_OK) == 0;
}

bool GuestConnection::send(const Bytes& data)
{
    // The driver allows you to work with only one open file
    int fdDev = open(m_address.c_str(), O_WRONLY);
    if (fdDev < 0) {
        perror("open to send");
        return false;
    }

    bool status = sendToFd(fdDev, data);

    close(fdDev);
    return true;
}

std::pair<bool, Bytes> GuestConnection::receive()
{
    // The driver allows you to work with only one open file
    int fdDev = open(m_address.c_str(), O_RDONLY);
    if (fdDev < 0) {
        perror("open to receive");
        return { false, Bytes() };
    }

    auto status = receiveFromFd(fdDev);

    close(fdDev);
    return status;
}