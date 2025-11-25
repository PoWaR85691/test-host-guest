#include "hostconnection.h"

#include <cstring>
#include <iostream>
#include <string>
#include <string_view>

int main(int argc, char **argv)
{
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " PATH_TO_SOCKET RESPONSE_DATA\n";
        return 1;
    }

    std::string address = argv[1];
    std::string_view svResponce = argv[2];

    HostConnection connection(address);
    if (!connection.isValid()) {
        std::cerr << "Cannot connect to " << address << "\n";
        return 1;
    }

    auto [status, data] = connection.receive();
    if (!status) {
        std::cerr << "Error to receive data\n";
        return 1;
    }

    std::string request{ data.begin(), data.end() };
    std::cout << "Request: " << request << "\n";

    Bytes response{ svResponce.begin(), svResponce.end() };
    if (!connection.send(response)) {
        std::cerr << "Error to send response\n";
        return 1;
    }

    return 0;
}