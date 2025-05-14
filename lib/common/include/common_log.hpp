
#pragma once

#include <string>
#include <iostream>
#include <format>
#include <chrono>
#include <filesystem>
#include <stdexcept>

// enable format("{}", std::filesystem::path )
template <class CharT>
struct std::formatter<std::filesystem::path, CharT>
    : std::formatter<std::basic_string<CharT>, CharT> // reuse the string formatter
{
    auto format(const std::filesystem::path &p,
                std::format_context &ctx) const
    {
        return std::formatter<std::basic_string<CharT>, CharT>::format(
            p.template string<CharT>(), ctx); // or u8string/u16string, etc.
    }
};

namespace ssp4cpp::common
{

    enum class LogLevel : int
    {
        trace,
        debug,
        info,
        success,
        warning,
        error,
        fatal
    };

    class Logger
    {
    public:
        static inline bool enabled = false;
        static inline LogLevel static_level = LogLevel::debug;

        Logger(LogLevel level)
        {
            Logger::enabled = true;
            Logger::static_level = level;
        }

        template <typename... Args>
        static void trace(std::format_string<Args...> s, Args &&...args)
        {
            log<LogLevel::trace>(s, std::forward<Args>(args)...);
        }

        template <typename... Args>
        static void debug(std::format_string<Args...> s, Args &&...args)
        {
            log<LogLevel::debug>(s, std::forward<Args>(args)...);
        }

        template <typename... Args>
        static void info(std::format_string<Args...> s, Args &&...args)
        {
            log<LogLevel::info>(s, std::forward<Args>(args)...);
        }

        template <typename... Args>
        static void success(std::format_string<Args...> s, Args &&...args)
        {
            log<LogLevel::success>(s, std::forward<Args>(args)...);
        }

        template <typename... Args>
        static void warning(std::format_string<Args...> s, Args &&...args)
        {
            log<LogLevel::warning>(s, std::forward<Args>(args)...);
        }

        template <typename... Args>
        static void error(std::format_string<Args...> s, Args &&...args)
        {
            log<LogLevel::error>(s, std::forward<Args>(args)...);
        }

        template <typename... Args>
        static void fatal(std::format_string<Args...> s, Args &&...args)
        {
            log<LogLevel::fatal>(s, std::forward<Args>(args)...);
        }

        template <LogLevel Level, typename... Args>
        static void log(std::format_string<Args...> s, Args &&...args)
        {
            if (Level >= Logger::static_level)
            {
                const auto time = std::chrono::system_clock::now();

                // const auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
                //                     time.time_since_epoch())
                //                     .count();
    
                auto str = std::format(s, std::forward<Args>(args)...);
                
                std::cout << std::format("[{}] {} - {}", log_level_to_str(Level), time, str) << std::endl ;
            }
        }

    private:
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