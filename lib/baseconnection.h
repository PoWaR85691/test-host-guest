#ifndef BASECONNECTION_H
#define BASECONNECTION_H

#include <cstdint>
#include <utility>
#include <vector>

using Bytes = std::vector<uint8_t>;

class BaseConnection
{
public:
    virtual bool isValid() const = 0;

    virtual bool send(const Bytes& data) = 0;
    virtual std::pair<bool, Bytes> receive() = 0;
};

#endif
