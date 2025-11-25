#ifndef GUESTCONNECTION_H
#define GUESTCONNECTION_H

#include "baseconnection.h"
#include <string>

class GuestConnection : public BaseConnection
{
public:
    GuestConnection(const std::string& address);

    bool isValid() const override;

    bool send(const Bytes& data) override;
    std::pair<bool, Bytes> receive() override;

private:
    std::string m_address;
};

#endif