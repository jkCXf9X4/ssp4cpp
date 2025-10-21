

#include "utils/socket.hpp"
#include <kissnet.hpp>



namespace ssp4cpp::utils
{

    static kissnet::tcp_socket* as_socket(void* ptr)
    {
        return  static_cast<kissnet::tcp_socket*>(ptr);
    }
    
    SocketWrapper::SocketWrapper(const std::string &adress)
    {
        socket = new kissnet::tcp_socket(kissnet::endpoint(adress));
    }

    SocketWrapper::~SocketWrapper()
    {
        as_socket(socket)->close();
        as_socket(socket)->shutdown();
        delete as_socket(socket);
        socket = nullptr;
    }
    
    bool SocketWrapper::connect()
    {
        return as_socket(socket)->connect() == kissnet::socket_status::valid;
    }

    bool SocketWrapper::send(std::byte * payload, size_t size)
    {
        as_socket(socket)->send(payload, size);
        return true;
    }

    bool SocketWrapper::is_valid()
    {
        return socket != nullptr && as_socket(socket)->is_valid();
    }

    bool SocketWrapper::close()
    {
        as_socket(socket)->close();
        return true;
    }

}