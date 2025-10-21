#pragma once

#include <kissnet.hpp>


// #include <chrono>
// #include <ctime>
// #include <format>
// #include <fstream>
// #include <iomanip>
// #include <iostream>
// #include <mutex>
// #include <sstream>
// #include <stdexcept>
// #include <string>
// #include <string_view>
// #include <source_location>


namespace ssp4cpp::utils
{

    class SocketWrapper
    {
    public:
        static inline std::unique_ptr<kissnet::tcp_socket> socket;

        SocketWrapper(const std::string &adress)
        {
            socket = std::make_unique<kissnet::tcp_socket>(kissnet::endpoint(adress));
        }
        
        bool connect()
        {
            return socket->connect() == kissnet::socket_status::valid;
        }

        bool send(std::byte * payload, size_t size)
        {
            socket->send(payload, size);
            return true;
        }

        bool is_valid()
        {
            return socket != nullptr && socket->is_valid();
        }

        bool close()
        {
            return true;
        }
    };
}