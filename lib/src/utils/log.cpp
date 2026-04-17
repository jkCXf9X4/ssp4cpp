#include "ssp4cpp/utils/log.hpp"

#include "quill/Backend.h"
#include "quill/LogFunctions.h"
#include "quill/SimpleSetup.h"
#include "quill/sinks/ConsoleSink.h"
#include "quill/sinks/FileSink.h"
#include "quill/sinks/JsonSink.h"

#include <algorithm>
#include <chrono>
#include <memory>
#include <mutex>
#include <stdexcept>
#include <vector>

namespace ssp4cpp::utils::log
{
    namespace
    {
        struct Logging
        {
            std::vector<std::shared_ptr<quill::Sink>> default_sinks{};
        };

        quill::BackendOptions backend_options()
        {
            quill::BackendOptions options;
            options.sleep_duration = std::chrono::nanoseconds{0};
            options.enable_yield_when_idle = true;
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

    void preallocate()
    {
        ensure_backend_started();
        Frontend::preallocate();
    }

    void init_logging()
    {
        preallocate();
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

    Logger* make_logger(std::string const& name)
    {
        preallocate();

        auto const& default_sinks = logging_state().default_sinks;
        if (default_sinks.empty())
        {
            throw std::runtime_error("Tried to create logger without sinks.");
        }

        auto logger = Frontend::create_or_get_logger(name, default_sinks);
        logger->set_log_level(quill::LogLevel::Debug);
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
