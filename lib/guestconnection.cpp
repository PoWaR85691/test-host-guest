#include "guestconnection.h"

#include <fcntl.h>
#include <string_view>
#include <unistd.h>

#include "common.h"

using namespace std::string_literals;

GuestConnection::GuestConnection(std::string_view address)
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
    int fdDev = openDev(O_WRONLY, "send");
    if (fdDev < 0) {
        return false;
    }

    bool status = sendToFd(fdDev, data);

    close(fdDev);
    return true;
}

std::pair<bool, Bytes> GuestConnection::receive()
{
    // The driver allows you to work with only one open file
    int fdDev = openDev(O_RDONLY, "receive");
    if (fdDev < 0) {
        return { false, Bytes() };
    }

    auto status = receiveFromFd(fdDev);

    close(fdDev);
    return status;
}

int GuestConnection::openDev(int mode, std::string_view info)
{
    int fdDev = open(m_address.c_str(), mode);
    if (fdDev < 0) {
        perror(("open to "s + std::string(info)).c_str());
        return -1;
    }
    return fdDev;
}