#ifndef GUESTCONNECTION_H
#define GUESTCONNECTION_H

#include "baseconnection.h"
#include <string>
#include <string_view>

class GuestConnection : public BaseConnection
{
public:
    GuestConnection(std::string_view address);

    bool isValid() const override;

    bool send(const Bytes& data) override;
    std::pair<bool, Bytes> receive() override;

private:
    int openDev(int mode, std::string_view info);

private:
    std::string m_address;
};

#endif