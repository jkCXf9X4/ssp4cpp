#pragma once

#include "quill/Frontend.h"
#include "quill/LogMacros.h"
#include "quill/Logger.h"
#include "quill/backend/BackendOptions.h"
#include "quill/core/FrontendOptions.h"
#include <cstddef>
#include <cstdint>
#include <filesystem>
#include <string>

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

    void preallocate();

    void init_logging();
    void add_console(quill::LogLevel level);
    void add_file_sink(std::filesystem::path const& log_file, quill::LogLevel level);
    void add_json_sink(std::filesystem::path const& log_file, quill::LogLevel level);
    Logger* make_logger(std::string const& name);
    Logger* make_logger(std::string const& name, quill::LogLevel level);
    Logger* simple_logger();
}
