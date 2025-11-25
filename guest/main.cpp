#include "guestconnection.h"

#include <iostream>

int main(int argc, char **argv)
{
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " PATH_TO_DEV REQUEST_DATA\n";
        return 1;
    }

    std::string address = argv[1];
    std::string_view svRequest = argv[2];

    GuestConnection connection(address);
    if (!connection.isValid()) {
        std::cerr << "Cannot connect to " << address << "\n";
        return 1;
    }

    Bytes request{ svRequest.begin(), svRequest.end() };
    if (!connection.send(request)) {
        std::cerr << "Error to send request\n";
        return 1;
    }

    auto [status, data] = connection.receive();
    if (!status) {
        std::cerr << "Error to receive data\n";
        return 1;
    }

    std::string response{ data.begin(), data.end() };
    std::cout << "Response: " << response << "\n";

    return 0;
}