#ifndef HOSTCONNECTION_H
#define HOSTCONNECTION_H

#include "baseconnection.h"
#include <string_view>

class HostConnection : public BaseConnection
{
public:
    HostConnection(std::string_view address);
    ~HostConnection();

    bool isValid() const override;

    bool send(const Bytes& data) override;
    std::pair<bool, Bytes> receive() override;

private:
    int m_fdSock = -1;
};

#endif