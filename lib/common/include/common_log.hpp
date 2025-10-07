
#pragma once

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
            return "ext trace";
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
    public:
        static inline bool file_sink_enabled = false;
        static inline std::ofstream file_sink_stream;
        static inline std::string file_sink_path;

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
            std::unique_lock<std::mutex> lock(Logger::print_mutex);

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
            std::unique_lock<std::mutex> lock(Logger::print_mutex);

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
            std::unique_lock<std::mutex> lock(Logger::print_mutex);
            return Logger::file_sink_enabled && Logger::file_sink_stream.is_open();
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
            Logger::write_to_file(name, Level, str);
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

            const auto time = std::chrono::system_clock::now();
            const auto str_time = std::format("{}", time);

            Logger::file_sink_stream << build_logfmt_entry(str_time, logger_name, level, message) << '\n';
            Logger::file_sink_stream.flush();
        }

        static std::string build_logfmt_entry(const std::string &time,
                                              const std::string &logger_name,
                                              LogLevel level,
                                              const std::string &message)
        {
            std::ostringstream entry;
            entry << "ts=" << time
                  << " level=\"" << escape_logfmt_component(log_level_to_str(level)) << "\""
                  << " logger=\"" << escape_logfmt_component(logger_name) << "\""
                  << " msg=\"" << escape_logfmt_component(message) << "\"";

            return entry.str();
        }

        static std::string escape_logfmt_component(std::string_view component)
        {
            std::string escaped;
            escaped.reserve(component.size());

            for (const char c : component)
            {
                if (c == '"' || c == '\\')
                {
                    escaped.push_back('\\');
                }

                escaped.push_back(c);
            }

            return escaped;
        }
    };

}
