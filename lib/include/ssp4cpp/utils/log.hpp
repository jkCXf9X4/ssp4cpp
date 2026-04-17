#pragma once

#include "quill/Backend.h"
#include "quill/Frontend.h"
#include "quill/LogFunctions.h"
#include "quill/LogMacros.h"
#include "quill/Logger.h"
#include "quill/SimpleSetup.h"
#include "quill/backend/BackendOptions.h"
#include "quill/core/FrontendOptions.h"

#include "quill/sinks/ConsoleSink.h"
#include "quill/sinks/FileSink.h"
#include "quill/sinks/JsonSink.h"

#include <algorithm>
#include <chrono>
#include <filesystem>
#include <memory>
#include <mutex>
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
    struct HotPathFrontendOptions
    {
        static constexpr quill::QueueType queue_type = quill::QueueType::UnboundedBlocking;
        static constexpr size_t initial_queue_capacity = 32u * 1024u * 1024u; // 32Mb
        static constexpr uint32_t blocking_queue_retry_interval_ns = 200;
        static constexpr size_t unbounded_queue_max_capacity = 2ull * 1024u * 1024u * 1024u; // 2 GiB
        static constexpr quill::HugePagesPolicy huge_pages_policy = quill::HugePagesPolicy::Never;
    };

    using Frontend = quill::FrontendImpl<HotPathFrontendOptions>;
    using Logger = typename Frontend::logger_t;

    inline quill::BackendOptions backend_options()
    {
        quill::BackendOptions options;
        options.sleep_duration = std::chrono::nanoseconds{0};
        options.enable_yield_when_idle = true;
        options.log_timestamp_ordering_grace_period = std::chrono::microseconds{0};
        options.sink_min_flush_interval = std::chrono::milliseconds{1000};
        return options;
    }

    inline void ensure_backend_started()
    {
        static std::once_flag start_once;
        std::call_once(start_once, []
        {
            quill::Backend::start<HotPathFrontendOptions>(backend_options(), quill::SignalHandlerOptions{});
        });
    }

    inline void preallocate()
    {
        ensure_backend_started();
        Frontend::preallocate();
    }

    struct Logging
    {
        std::vector<std::shared_ptr<quill::Sink>> default_sinks{};
    };

    static Logging log_common{};

    inline void add_default_sink(std::shared_ptr<quill::Sink> const& sink)
    {
        auto it = std::find(log_common.default_sinks.begin(), log_common.default_sinks.end(), sink);
        if (it == log_common.default_sinks.end())
        {
            log_common.default_sinks.push_back(sink);
        }
    }

    inline void init_logging()
    {
        preallocate();
    }

    inline void add_console(quill::LogLevel level)
    {
        auto console_sink =
            Frontend::create_or_get_sink<quill::ConsoleSink>("console");
        console_sink->set_log_level_filter(level);

        add_default_sink(console_sink);
    }

    inline void add_file_sink(std::filesystem::path const& log_file, quill::LogLevel level)
    {
        auto file_sink =
            Frontend::create_or_get_sink<quill::FileSink>(
                log_file.string(),
                []
                {
                    quill::FileSinkConfig cfg;
                    cfg.set_open_mode('w');
                    cfg.set_filename_append_option(quill::FilenameAppendOption::StartDateTime);
                    return cfg;
                }());

        file_sink->set_log_level_filter(level);
        add_default_sink(file_sink);
    }

    inline void add_json_sink(std::filesystem::path const& log_file, quill::LogLevel level)
    {
        auto json_sink =
            Frontend::create_or_get_sink<quill::JsonFileSink>(
                log_file.string(),
                []
                {
                    quill::FileSinkConfig cfg;
                    cfg.set_open_mode('w');
                    cfg.set_filename_append_option(quill::FilenameAppendOption::StartDateTime);
                    return cfg;
                }());

        json_sink->set_log_level_filter(level);
        add_default_sink(json_sink);
    }

    inline Logger* make_logger(std::string const& name)
    {
        preallocate();

        if (log_common.default_sinks.empty())
        {
            throw std::runtime_error("Tried to create logger without sinks.");
        }

        auto logger = Frontend::create_or_get_logger(name, log_common.default_sinks);
        logger->set_log_level(quill::LogLevel::TraceL1);
        return logger;
    }

    inline Logger* make_logger(std::string const& name, quill::LogLevel level)
    {
        Logger* logger = make_logger(name);
        logger->set_log_level(level);
        return logger;
    }

    inline Logger* simple_logger()
    {
        preallocate();

        constexpr char logger_name[] = "stdout";
        Logger* logger = Frontend::get_logger(logger_name);

        if (!logger)
        {
            auto sink = Frontend::create_or_get_sink<quill::ConsoleSink>(logger_name);
            logger = Frontend::create_or_get_logger(
                logger_name,
                std::move(sink),
                quill::PatternFormatterOptions{
                    "%(time) [%(thread_id)] %(short_source_location:<28) LOG_%(log_level:<9) %(message)"});
        }

        return logger;
    }
}
