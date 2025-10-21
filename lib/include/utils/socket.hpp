#pragma once

#include <string>

namespace ssp4cpp::utils
{

    class SocketWrapper
    {
    public:
        static inline void* socket;

        SocketWrapper(const std::string &adress);

        ~SocketWrapper();
        
        bool connect();

        bool send(std::byte * payload, size_t size);
        bool is_valid();

        bool close();
    };
}