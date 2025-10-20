
#pragma once

#include <kissnet.hpp>
#include <utils/log_level.hpp>

#include <chrono>
#include <ctime>
#include <format>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <mutex>
#include <sstream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <source_location>

// If you import this file you will get the namespace
using namespace ssp4cpp::utils::log;

namespace ssp4cpp::utils::log
{

    /**
     * @brief Simple logger implementation used throughout the library.
     *
     * The logger provides several convenience functions for different
     * log levels. Each function ultimately forwards to the templated
     * log() method which handles formatting and output.
     */

    using enum LogLevel;

    class Logger
    {
        // namespace warning = LogLevel::
        // using LogLevel::debug as debug;

    public:
        static inline bool file_sink_enabled = false;
        static inline std::ofstream file_sink_stream;
        static inline std::string file_sink_path;

        static inline bool socket_sink_enabled = false;
        static inline std::unique_ptr<kissnet::tcp_socket> socket;

        static inline std::mutex print_mutex;

        std::string name;
        LogLevel console_level;

        Logger()
        {
            console_level = LogLevel::debug;
            name = "null";
        }

        Logger(std::string name_, LogLevel lvl)
        {
            console_level = lvl;
            name = name_;
        }

        static void enable_file_sink(const std::string &path, bool append = true)
        {
            std::ios_base::openmode mode = std::ios::out;
            mode |= append ? std::ios::app : std::ios::trunc;

            if (Logger::file_sink_stream.is_open())
            {
                Logger::file_sink_stream.close();
            }

            Logger::file_sink_stream.open(path, mode);

            if (!Logger::file_sink_stream.is_open())
            {
                Logger::file_sink_enabled = false;
                Logger::file_sink_path.clear();
                throw std::runtime_error("failed to open log file: " + path);
            }

            Logger::file_sink_enabled = true;
            Logger::file_sink_path = path;
        }

        static void disable_file_sink()
        {
            Logger::file_sink_enabled = false;
            Logger::file_sink_path.clear();

            if (Logger::file_sink_stream.is_open())
            {
                Logger::file_sink_stream.flush();
                Logger::file_sink_stream.close();
            }
        }

        static bool is_file_sink_enabled()
        {
            return Logger::file_sink_enabled && Logger::file_sink_stream.is_open();
        }

        static void enable_socket_sink(const std::string &adress)
        {
            Logger::socket = std::make_unique<kissnet::tcp_socket>(kissnet::endpoint(adress));
            if (Logger::socket->connect() == kissnet::socket_status::valid)
            {
                auto payload = make_cutelog_payload("!!cutelog!!format=json");
                Logger::socket->send((std::byte *)payload.data(), payload.size());
                Logger::socket_sink_enabled = true;
            }
            else
            {
                std::cout << "Failed to set up socket connection" << std::endl;
            }
        }

        static bool is_socket_sink_enabled()
        {
            return Logger::socket_sink_enabled && Logger::socket != nullptr && Logger::socket->is_valid();
        }

        auto operator()(LogLevel level, std::source_location loc = std::source_location::current())
        {
            return [=,this]<class... Args>(std::format_string<Args...> fmt, Args &&...args)
            {
                auto message = std::format(fmt, std::forward<Args>(args)...);
                // std::cout << message << std::endl;
                this->ll(level, loc, message);
            };
        }

        // Long log
        void ll(LogLevel level, std::source_location loc, std::string_view message) const
        {
            std::unique_lock<std::mutex> lock(Logger::print_mutex);
            auto log_level = log_level_to_str(level);

            if (level >= this->console_level)
            {
                auto formatted_msg = std::format("[{}][{}] {}", loc.function_name(), log_level, message);
                Logger::write_to_console(level, formatted_msg);
            }
            if (level > LogLevel::ext_trace)
            {
                auto json_str = build_json_entry(
                    this->name, log_level, message, loc.file_name(), loc.line(), loc.function_name());

                if (Logger::is_file_sink_enabled())
                    Logger::write_to_file(json_str);
                if (Logger::is_socket_sink_enabled())
                    Logger::write_to_socket(json_str);
            }
        }

    private:
        static void write_to_console(LogLevel level, const std::string_view message)
        {
            const std::string_view color_prefix = log_level_to_color(level);
            const std::string_view color_suffix = color_reset();

            if (level < LogLevel::error)
            {
                std::cout << color_prefix << message << color_suffix << "\n";
            }
            else
            {
                std::cerr << color_prefix << message << color_suffix << "\n";
            }
        }

        static void write_to_file(const std::string_view message)
        {
            if (!Logger::file_sink_stream.is_open())
            {
                Logger::file_sink_enabled = false;
                return;
            }

            Logger::file_sink_stream << message;
            Logger::file_sink_stream.flush();
        }

        static std::vector<uint8_t> make_cutelog_payload(const std::string_view json)
        {
            uint32_t len = static_cast<uint32_t>(json.size());
            uint32_t be = htonl(len); // convert to big-endian

            std::vector<uint8_t> out(4 + json.size());
            std::memcpy(out.data(), &be, 4);
            std::memcpy(out.data() + 4, json.data(), json.size());
            return out;
        }

        static void write_to_socket(const std::string_view message)
        {
            auto payload = make_cutelog_payload(message);
            Logger::socket->send((std::byte *)payload.data(), payload.size());
        }

        static std::string build_json_entry(const std::string_view logger_name,
                                            const std::string_view level,
                                            const std::string_view message,
                                            const std::string_view file,
                                            const uint32_t line,
                                            const std::string_view function)
        {

            const auto time = std::chrono::system_clock::now();
            const auto str_time = std::format("{}", time);

            std::ostringstream entry;
            entry << '{';
            entry << "\"time\":\"" << str_time << "\", ";
            entry << "\"name\":\"" << logger_name << "\", ";
            entry << "\"level\":\"" << level << "\", ";
            entry << "\"msg\":\"" << std::format("[{}] {}", function, message) << "\", ";
            entry << "\"file\":\"" << file << "\", ";
            entry << "\"line\":\"" << line << "\", ";
            entry << "\"function\":\"" << function << "\"";
            entry << "}\n";

            return entry.str();
        }

        static std::string escape_json_string(std::string_view component)
        {
            std::string escaped;
            escaped.reserve(component.size());

            for (const char c : component)
            {
                switch (c)
                {
                case '"':
                    escaped.append("\\\"");
                    break;
                case '\\':
                    escaped.append("\\\\");
                    break;
                case '\b':
                    escaped.append("\\b");
                    break;
                case '\f':
                    escaped.append("\\f");
                    break;
                case '\n':
                    escaped.append("\\n");
                    break;
                case '\r':
                    escaped.append("\\r");
                    break;
                case '\t':
                    escaped.append("\\t");
                    break;
                default:
                    if (static_cast<unsigned char>(c) < 0x20)
                    {
                        const unsigned char uc = static_cast<unsigned char>(c);
                        constexpr char hex_digits[] = "0123456789ABCDEF";
                        escaped.append("\\u00");
                        escaped.push_back(hex_digits[(uc >> 4) & 0x0F]);
                        escaped.push_back(hex_digits[uc & 0x0F]);
                    }
                    else
                    {
                        escaped.push_back(c);
                    }
                    break;
                }
            }

            return escaped;
        }
    };

}
