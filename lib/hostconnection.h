#ifndef HOSTCONNECTION_H
#define HOSTCONNECTION_H

#include "baseconnection.h"
#include <string>

class HostConnection : public BaseConnection
{
public:
    HostConnection(const std::string& address);
    ~HostConnection();

    bool isValid() const override;

    bool send(const Bytes& data) override;
    std::pair<bool, Bytes> receive() override;

private:
    int m_fdSock = -1;
};

#endif