
#pragma once

#include <kissnet.hpp>

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

namespace ssp4cpp::common
{

    /**
     * @brief Severity levels used by the ::Logger class.
     */
    enum class LogLevel : int
    {
        ext_trace, /**< Extremely verbose trace messages */
        trace,     /**< Verbose tracing information */
        debug,     /**< Debug information */
        info,      /**< General information */
        success,   /**< Successful operations */
        warning,   /**< Warnings */
        error,     /**< Error conditions */
        fatal      /**< Fatal errors */
    };

    /**
     * @brief Convert a LogLevel to its human readable string
     *        representation.
     */
    static std::string log_level_to_str(LogLevel level)
    {
        switch (level)
        {
        case LogLevel::ext_trace:
            return "ext_trace";
        case LogLevel::trace:
            return "trace";
        case LogLevel::debug:
            return "debug";
        case LogLevel::info:
            return "info";
        case LogLevel::success:
            return "success";
        case LogLevel::warning:
            return "warning";
        case LogLevel::error:
            return "error";
        case LogLevel::fatal:
            return "fatal";
        default:
            return "unknown";
        }
    }

    // https://i.sstatic.net/9UVnC.png
    static constexpr std::string_view log_level_to_color(LogLevel level)
    {
        switch (level)
        {
        case LogLevel::ext_trace:
            return "\033[90m"; // Bright black
        case LogLevel::trace:
            return "\033[36m"; // Cyan
        case LogLevel::debug:
            return "\033[94m"; // Blue
        case LogLevel::info:
            return "\033[97m"; // White
        case LogLevel::success:
            return "\033[32m"; // Green
        case LogLevel::warning:
            return "\033[33m"; // Yellow
        case LogLevel::error:
            return "\033[31m"; // Red
        case LogLevel::fatal:
            return "\033[95m"; // Bright magenta
        default:
            return "\033[0m";
        }
    }

    static constexpr std::string_view color_reset()
    {
        return "\033[0m";
    }

    /**
     * @brief Parse a string representation of a log level.
     */
    static LogLevel str_to_log_level(std::string string)
    {
        if (string == "ext_trace")
            return LogLevel::ext_trace;
        else if (string == "trace")
            return LogLevel::trace;
        else if (string == "debug")
            return LogLevel::debug;
        else if (string == "info")
            return LogLevel::info;
        else if (string == "success")
            return LogLevel::success;
        else if (string == "warning")
            return LogLevel::warning;
        else if (string == "error")
            return LogLevel::error;
        else if (string == "fatal")
            return LogLevel::fatal;
        else
            return LogLevel::info;
    }

    /**
     * @brief Simple logger implementation used throughout the library.
     *
     * The logger provides several convenience functions for different
     * log levels. Each function ultimately forwards to the templated
     * log() method which handles formatting and output.
     */
    class Logger
    {
        // using LogLevel::debug as debug;

    public:
        static inline bool file_sink_enabled = false;
        static inline std::ofstream file_sink_stream;
        static inline std::string file_sink_path;

        static inline bool socket_sink_enabled = false;
        static inline std::unique_ptr<kissnet::tcp_socket> socket;

        static inline std::mutex print_mutex;

        std::string name;
        LogLevel level;

        Logger()
        {
            level = LogLevel::debug;
            name = "null";
        }

        Logger(std::string name_, LogLevel lvl)
        {
            level = lvl;
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
                Logger::socket_sink_enabled = true;
                auto payload = make_cutelog_payload("!!cutelog!!format=json");
                Logger::socket->send((std::byte*)payload.data(), payload.size());
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

        template <typename... Args>
        void ext_trace(std::format_string<Args...> s, Args &&...args)
        {
            log<LogLevel::ext_trace>(s, std::forward<Args>(args)...);
        }

        template <typename... Args>
        void trace(std::format_string<Args...> s, Args &&...args)
        {
            log<LogLevel::trace>(s, std::forward<Args>(args)...);
        }

        template <typename... Args>
        void debug(std::format_string<Args...> s, Args &&...args)
        {
            log<LogLevel::debug>(s, std::forward<Args>(args)...);
        }

        template <typename... Args>
        void info(std::format_string<Args...> s, Args &&...args)
        {
            log<LogLevel::info>(s, std::forward<Args>(args)...);
        }

        template <typename... Args>
        void success(std::format_string<Args...> s, Args &&...args)
        {
            log<LogLevel::success>(s, std::forward<Args>(args)...);
        }

        template <typename... Args>
        void warning(std::format_string<Args...> s, Args &&...args)
        {
            log<LogLevel::warning>(s, std::forward<Args>(args)...);
        }

        template <typename... Args>
        void error(std::format_string<Args...> s, Args &&...args)
        {
            log<LogLevel::error>(s, std::forward<Args>(args)...);
        }

        template <typename... Args>
        void fatal(std::format_string<Args...> s, Args &&...args)
        {
            log<LogLevel::fatal>(s, std::forward<Args>(args)...);
        }

        /**
         * @brief Generic logging function invoked by the level specific helpers.
         *
         * @tparam Level   Compile time log level.
         * @tparam Args    Argument pack for std::format.
         * @param s        Format string.
         * @param args     Arguments to format into the message.
         */
        template <LogLevel Level, typename... Args>
        void log(std::format_string<Args...> s, Args &&...args)
        {
            std::unique_lock<std::mutex> lock(Logger::print_mutex);
            auto str = std::format(s, std::forward<Args>(args)...);
            if (Level >= level)
            {
                Logger::write_to_console<Level>(name, str);
            }
            if (Level > LogLevel::ext_trace)
            {
                if (Logger::is_file_sink_enabled())
                    Logger::write_to_file(name, Level, str);
                if (Logger::is_socket_sink_enabled())
                    Logger::write_to_socket(name, Level, str);
            }
        }

    private:
        template <LogLevel Level>
        static void write_to_console(const std::string name, const std::string &message)
        {
            auto formated_msg = std::format("[{}][{}] {}", name, log_level_to_str(Level), message);

            const std::string_view color_prefix = log_level_to_color(Level);
            const std::string_view color_suffix = color_reset();

            if constexpr (Level < LogLevel::error)
            {
                std::cout << color_prefix << formated_msg << color_suffix << "\n";
            }
            else
            {
                std::cerr << color_prefix << formated_msg << color_suffix << "\n";
            }
        }

        static void write_to_file(const std::string &logger_name,
                                  LogLevel level,
                                  const std::string &message)
        {
            if (!Logger::file_sink_stream.is_open())
            {
                Logger::file_sink_enabled = false;
                return;
            }

            Logger::file_sink_stream << build_json_entry(logger_name, level, message);
            Logger::file_sink_stream.flush();
        }

        static std::vector<uint8_t> make_cutelog_payload(const std::string &json)
        {
            uint32_t len = static_cast<uint32_t>(json.size());
            uint32_t be = htonl(len); // convert to big-endian

            std::vector<uint8_t> out(4 + json.size());
            std::memcpy(out.data(), &be, 4);
            std::memcpy(out.data() + 4, json.data(), json.size());
            return out;
        }

        static void write_to_socket(const std::string &logger_name,
                                    LogLevel level,
                                    const std::string &message)
        {
            auto payload = make_cutelog_payload(build_json_entry(logger_name, level, message));
            Logger::socket->send((std::byte*)payload.data(), payload.size());
        }

        static std::string build_json_entry(const std::string &logger_name,
                                            LogLevel level,
                                            const std::string &message)
        {

            const auto time = std::chrono::system_clock::now();
            const auto str_time = std::format("{}", time);

            std::ostringstream entry;
            entry << '{';
            entry << "\"time\":\"" << str_time << "\", ";
            entry << "\"level\":\"" << log_level_to_str(level) << "\", ";
            entry << "\"name\":\"" << logger_name << "\", ";
            entry << "\"msg\":\"" << message << "\"";
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
