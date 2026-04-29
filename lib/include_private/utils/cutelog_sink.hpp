#pragma once

#include "quill/sinks/Sink.h"

#include <cstdint>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

namespace ssp4cpp::utils::log
{
    class CutelogSink final : public quill::Sink
    {
    public:
        CutelogSink(std::string host, uint16_t port);
        ~CutelogSink() override;

        void write_log(
            quill::MacroMetadata const* log_metadata,
            uint64_t log_timestamp,
            std::string_view thread_id,
            std::string_view thread_name,
            std::string const& process_id,
            std::string_view logger_name,
            quill::LogLevel log_level,
            std::string_view log_level_description,
            std::string_view log_level_short_code,
            std::vector<std::pair<std::string, std::string>> const* named_args,
            std::string_view log_message,
            std::string_view log_statement) override;

        void flush_sink() override;

    private:
        static void append_json_string(std::string& out, std::string_view value);
        static void append_json_escaped(std::string& out, std::string_view value);

        int connect_socket();
        bool send_payload(std::string_view payload);
        void close_socket();

        std::string host_;
        uint16_t port_;
        int fd_;
        std::string json_payload_;
    };
}
