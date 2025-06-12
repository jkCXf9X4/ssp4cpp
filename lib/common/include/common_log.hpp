
#pragma once

#include <string>
#include <iostream>
#include <format>
#include <chrono>
#include <filesystem>
#include <stdexcept>
#include <mutex>

namespace ssp4cpp::common
{

    /**
     * @brief Severity levels used by the ::Logger class.
     */
    enum class LogLevel : int
    {
        ext_trace,  /**< Extremely verbose trace messages */
        trace,      /**< Verbose tracing information */
        debug,      /**< Debug information */
        info,       /**< General information */
        success,    /**< Successful operations */
        warning,    /**< Warnings */
        error,      /**< Error conditions */
        fatal       /**< Fatal errors */
    };

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
        static inline bool enabled = false;
        static inline LogLevel static_level = LogLevel::debug;
        static inline std::mutex print_mutex;

        std::string name;
        LogLevel level;

        Logger()
        {
            Logger::enabled = true;
            level = LogLevel::debug;
            name = "null";
        }

        Logger(std::string name_, LogLevel lvl)
        {
            Logger::enabled = true;
            level = lvl;
            name = name_;
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

        void new_line()
        {
            std::cout << std::endl;
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
            if (Level >= level)
            {
                const auto time = std::chrono::system_clock::now();
                auto str = std::format(s, std::forward<Args>(args)...);
                auto out = std::format("[{}][{}][{}] {}", name, log_level_to_str(Level), time, str);

                {
                    std::unique_lock<std::mutex> lock(Logger::print_mutex);
                    if constexpr (Level < LogLevel::error)
                    {
                        std::cout << out << std::endl;
                    }
                    else
                    {
                        std::cerr << out << std::endl;
                    }
                }
            }
        }

        /**
         * @brief Static helper for logging without an instance.
         *
         * Prefer using an instance of ::Logger when possible. The behaviour is
         * the same as log() but uses the static log level for filtering.
         */
        template <LogLevel Level, typename... Args>
        static void slog(std::format_string<Args...> s, Args &&...args)
        {
            if (Level >= Logger::static_level)
            {
                const auto time = std::chrono::system_clock::now();
                auto str = std::format(s, std::forward<Args>(args)...);
                auto out = std::format("[{}][{}] {}", log_level_to_str(Level), time, str);

                {
                    std::unique_lock<std::mutex> lock(Logger::print_mutex);
                    if constexpr (Level < LogLevel::error)
                    {
                        std::cout << out << std::endl;
                    }
                    else
                    {
                        std::cerr << out << std::endl;
                    }
                }
            }
        }

    private:
        /**
         * @brief Convert a LogLevel to its human readable string
         *        representation.
         */
        static std::string log_level_to_str(LogLevel level)
        {
            switch (level)
            {
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

        /**
         * @brief Parse a string representation of a log level.
         */
        static LogLevel str_to_log_level(std::string string)
        {
            if (string == "trace")
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
    };

}