#include "utils/cutelog_sink.hpp"

#include "quill/core/MacroMetadata.h"

#include <arpa/inet.h>
#include <array>
#include <cerrno>
#include <cstring>
#include <memory>
#include <netdb.h>
#include <stdexcept>
#include <string>
#include <sys/socket.h>
#include <unistd.h>

namespace ssp4cpp::utils::log
{
    CutelogSink::CutelogSink(std::string host, uint16_t port)
        : host_(std::move(host)),
          port_(port),
          fd_(connect_socket())
    {
        static constexpr std::string_view json_format_command = "!!cutelog!!format=json";
        if (!send_payload(json_format_command))
        {
            throw std::runtime_error("Failed to send cutelog JSON format command.");
        }
    }

    CutelogSink::~CutelogSink()
    {
        close_socket();
    }

    void CutelogSink::write_log(
        quill::MacroMetadata const* log_metadata,
        uint64_t log_timestamp,
        std::string_view thread_id,
        std::string_view thread_name,
        std::string const& process_id,
        std::string_view logger_name,
        quill::LogLevel,
        std::string_view log_level_description,
        std::string_view,
        std::vector<std::pair<std::string, std::string>> const* named_args,
        std::string_view log_message,
        std::string_view)
    {
        if (fd_ < 0)
        {
            return;
        }

        json_payload_.clear();
        json_payload_.append("{\"created\":");
        json_payload_.append(std::to_string(static_cast<double>(log_timestamp) / 1'000'000'000.0));
        json_payload_.append(",\"levelname\":");
        append_json_string(json_payload_, log_level_description);
        json_payload_.append(",\"name\":");
        append_json_string(json_payload_, logger_name);
        json_payload_.append(",\"msg\":");
        append_json_string(json_payload_, log_message);
        json_payload_.append(",\"pathname\":");
        append_json_string(json_payload_, log_metadata->file_name());
        json_payload_.append(",\"lineno\":");
        json_payload_.append(log_metadata->line());
        json_payload_.append(",\"thread\":");
        append_json_string(json_payload_, thread_id);
        json_payload_.append(",\"threadName\":");
        append_json_string(json_payload_, thread_name);
        json_payload_.append(",\"process\":");
        append_json_string(json_payload_, process_id);

        if (named_args)
        {
            for (auto const& [key, value] : *named_args)
            {
                json_payload_.append(",\"extra.");
                append_json_escaped(json_payload_, key);
                json_payload_.append("\":");
                append_json_string(json_payload_, value);
            }
        }

        json_payload_.append("}");
        send_payload(json_payload_);
    }

    void CutelogSink::flush_sink()
    {
    }

    void CutelogSink::append_json_string(std::string& out, std::string_view value)
    {
        out.push_back('"');
        append_json_escaped(out, value);
        out.push_back('"');
    }

    void CutelogSink::append_json_escaped(std::string& out, std::string_view value)
    {
        static constexpr std::array<char, 16> hex = {
            '0', '1', '2', '3', '4', '5', '6', '7',
            '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};

        for (unsigned char ch : value)
        {
            switch (ch)
            {
            case '"':
                out.append("\\\"");
                break;
            case '\\':
                out.append("\\\\");
                break;
            case '\b':
                out.append("\\b");
                break;
            case '\f':
                out.append("\\f");
                break;
            case '\n':
                out.append("\\n");
                break;
            case '\r':
                out.append("\\r");
                break;
            case '\t':
                out.append("\\t");
                break;
            default:
                if (ch < 0x20)
                {
                    out.append("\\u00");
                    out.push_back(hex[ch >> 4]);
                    out.push_back(hex[ch & 0x0f]);
                }
                else
                {
                    out.push_back(static_cast<char>(ch));
                }
            }
        }
    }

    int CutelogSink::connect_socket()
    {
        addrinfo hints{};
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_STREAM;

        addrinfo* addresses = nullptr;
        int const status = getaddrinfo(host_.c_str(), std::to_string(port_).c_str(), &hints, &addresses);
        if (status != 0)
        {
            throw std::runtime_error("Failed to resolve cutelog endpoint " + host_ + ":" +
                                     std::to_string(port_) + ": " + gai_strerror(status));
        }

        std::unique_ptr<addrinfo, decltype(&freeaddrinfo)> address_guard(addresses, freeaddrinfo);
        for (addrinfo* address = addresses; address; address = address->ai_next)
        {
            int const fd = socket(address->ai_family, address->ai_socktype, address->ai_protocol);
            if (fd < 0)
            {
                continue;
            }

            if (connect(fd, address->ai_addr, address->ai_addrlen) == 0)
            {
                return fd;
            }

            int const connect_error = errno;
            close(fd);
            errno = connect_error;
        }

        throw std::runtime_error("Failed to connect to cutelog endpoint " + host_ + ":" +
                                 std::to_string(port_) + ": " + std::strerror(errno));
    }

    bool CutelogSink::send_payload(std::string_view payload)
    {
        if (payload.size() > UINT32_MAX)
        {
            close_socket();
            return false;
        }

        uint32_t const length = htonl(static_cast<uint32_t>(payload.size()));
        std::array<std::string_view, 2> buffers = {
            std::string_view{reinterpret_cast<char const*>(&length), sizeof(length)},
            payload};

        for (std::string_view buffer : buffers)
        {
            while (!buffer.empty())
            {
                ssize_t const sent = send(fd_, buffer.data(), buffer.size(), MSG_NOSIGNAL);
                if (sent < 0)
                {
                    if (errno == EINTR)
                    {
                        continue;
                    }
                    close_socket();
                    return false;
                }

                if (sent == 0)
                {
                    close_socket();
                    return false;
                }

                buffer.remove_prefix(static_cast<size_t>(sent));
            }
        }

        return true;
    }

    void CutelogSink::close_socket()
    {
        if (fd_ >= 0)
        {
            close(fd_);
            fd_ = -1;
        }
    }
}
