
#pragma once

#include <string>

namespace ssp4cpp::utils::log
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
}
