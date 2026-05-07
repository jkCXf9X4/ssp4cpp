#include "ssp4cpp/utils/log.hpp"

#include "utils/cutelog_sink.hpp"

#include "quill/Backend.h"
#include "quill/LogFunctions.h"
#include "quill/SimpleSetup.h"
#include "quill/sinks/ConsoleSink.h"
#include "quill/sinks/FileSink.h"
#include "quill/sinks/JsonSink.h"
#include "quill/sinks/NullSink.h"

#include <algorithm>
#include <chrono>
#include <memory>
#include <mutex>
#include <stdexcept>
#include <string>
#include <vector>
#include <iostream>

namespace ssp4cpp::utils::log
{
    namespace
    {
        struct Logging
        {
            std::vector<std::shared_ptr<quill::Sink>> default_sinks{};
        };

        quill::BackendOptions backend_options(bool backend_hot_optimization = true)
        {
            quill::BackendOptions options;
            if (backend_hot_optimization)
            {
                options.sleep_duration = std::chrono::nanoseconds{0};
                options.enable_yield_when_idle = true;
            }
            else
            {
                options.sleep_duration = std::chrono::milliseconds{1};
                options.enable_yield_when_idle = false;
            }

            options.log_timestamp_ordering_grace_period = std::chrono::microseconds{0};
            options.sink_min_flush_interval = std::chrono::milliseconds{1000};
            return options;
        }

        Logging& logging_state()
        {
            static Logging state{};
            return state;
        }

        void ensure_backend_started()
        {
            static std::once_flag start_once;
            std::call_once(start_once, []
            {
                quill::Backend::start<HotPathFrontendOptions>(backend_options(), quill::SignalHandlerOptions{});
            });
        }

        void add_default_sink(std::shared_ptr<quill::Sink> const& sink)
        {
            auto& default_sinks = logging_state().default_sinks;
            auto it = std::find(default_sinks.begin(), default_sinks.end(), sink);
            if (it == default_sinks.end())
            {
                default_sinks.push_back(sink);
            }
        }
    }


    void init_logging()
    {
        // if no sink is 
        auto const& default_sinks = logging_state().default_sinks;
        if (default_sinks.empty())
        {
            auto null_sink =
            Frontend::create_or_get_sink<quill::NullSink>("nullsink");
            add_default_sink(null_sink);

            std::cout << "\n\n!!!!\nWarning, no output sink is selected, prints will go to null\n!!!!\n";
        }

        Frontend::preallocate();

        ensure_backend_started();

    }

    void add_console(quill::LogLevel level)
    {
        auto console_sink =
            Frontend::create_or_get_sink<quill::ConsoleSink>("console");
        console_sink->set_log_level_filter(level);

        add_default_sink(console_sink);
    }

    void add_file_sink(std::filesystem::path const& log_file, quill::LogLevel level)
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

    void add_json_sink(std::filesystem::path const& log_file, quill::LogLevel level)
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

    void add_cutelog_sink(std::string const& host, uint16_t port, quill::LogLevel level)
    {
        auto cutelog_sink =
            Frontend::create_or_get_sink<CutelogSink>(
                "cutelog:" + host + ":" + std::to_string(port),
                host,
                port);

        cutelog_sink->set_log_level_filter(level);
        add_default_sink(cutelog_sink);
    }

    Logger* make_logger(std::string const& name)
    {

        auto const& default_sinks = logging_state().default_sinks;
        if (default_sinks.empty())
        {
            throw std::runtime_error("Tried to create logger without sinks.");
        }

        auto logger = Frontend::create_or_get_logger(name, default_sinks);
        logger->set_log_level(quill::LogLevel::Debug);
        quill::Frontend::preallocate();

        return logger;
    }

    Logger* make_logger(std::string const& name, quill::LogLevel level)
    {
        Logger* logger = make_logger(name);
        logger->set_log_level(level);
        return logger;
    }

    Logger* simple_logger()
    {
        ensure_backend_started();

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
