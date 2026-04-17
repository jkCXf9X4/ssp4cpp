#pragma once

#include "quill/LogFunctions.h"
#include "quill/Backend.h"
#include "quill/Frontend.h"
#include "quill/LogMacros.h"
#include "quill/Logger.h"

#include "quill/sinks/ConsoleSink.h"
#include "quill/sinks/FileSink.h"
#include "quill/sinks/JsonSink.h"

#include <filesystem>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

// log_toggle.hpp
#ifdef _LOG_
#define IF_LOG(stmt) \
    do               \
    {                \
        stmt         \
    } while (0)
#else
#define IF_LOG(stmt) \
    do               \
    {                \
    } while (0)
#endif

namespace ssp4cpp::utils::log
{

    struct Logging
    {
        std::vector<std::shared_ptr<quill::Sink>> default_sinks{};
    };

    static Logging log_common{};

    inline void init_logging()
    {
        quill::Backend::start();
    }

    inline void add_console(quill::LogLevel level)
    {
        auto console_sink =
            quill::Frontend::create_or_get_sink<quill::ConsoleSink>("console");
        console_sink->set_log_level_filter(level);

        log_common.default_sinks.push_back(console_sink);
    }

    inline void add_file_sink(std::filesystem::path const &log_file, quill::LogLevel level)
    {
        auto file_sink =
            quill::Frontend::create_or_get_sink<quill::FileSink>(
                log_file.string(),
                []
                {
                    quill::FileSinkConfig cfg;
                    cfg.set_open_mode('w');
                    cfg.set_filename_append_option(quill::FilenameAppendOption::StartDateTime);
                    return cfg;
                }());

        file_sink->set_log_level_filter(level);
        log_common.default_sinks.push_back(file_sink);
    }

    inline void add_json_sink(std::filesystem::path const &log_file, quill::LogLevel level)
    {
        auto json_sink =
            quill::Frontend::create_or_get_sink<quill::JsonFileSink>(
                log_file.string(),
                []
                {
                    quill::FileSinkConfig cfg;
                    cfg.set_open_mode('w');
                    cfg.set_filename_append_option(quill::FilenameAppendOption::StartDateTime);
                    return cfg;
                }());

        json_sink->set_log_level_filter(level);
        log_common.default_sinks.push_back(json_sink);
    }

    inline quill::Logger *make_logger(std::string const &name)
    {
        if (log_common.default_sinks.empty())
        {
            throw std::runtime_error("Tried to create logger without sinks.");
        }

        return quill::Frontend::create_or_get_logger(name, log_common.default_sinks);
    }

    inline quill::Logger *make_logger(std::string const &name, quill::LogLevel level)
    {
        quill::Logger *logger = make_logger(name);
        logger->set_log_level(level);
        return logger;
    }

    inline quill::Logger *simple_logger()
    {
        init_logging();
        add_console(quill::LogLevel::TraceL3);
        return make_logger("simple");
    }
}
