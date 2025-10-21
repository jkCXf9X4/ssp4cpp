#include <catch2/catch_test_macros.hpp>

#include "utils/log.hpp"

#include <algorithm>
#include <chrono>
#include <filesystem>
#include <fstream>
#include <string>

namespace fs = std::filesystem;
using namespace ssp4cpp::utils::log;

namespace
{

    fs::path make_unique_log_path()
    {
        const auto timestamp = std::chrono::steady_clock::now().time_since_epoch().count();
        return fs::temp_directory_path() / ("ssp4cpp_logger_test_" + std::to_string(timestamp) + ".log");
    }

    std::string read_file(const fs::path &path)
    {
        std::ifstream stream(path);
        return std::string(std::istreambuf_iterator<char>(stream), std::istreambuf_iterator<char>());
    }

} // namespace

TEST_CASE("Logger writes formatted entry to the file sink")
{
    const auto log_path = make_unique_log_path();
    if (fs::exists(log_path))
    {
        fs::remove(log_path);
    }

    Logger::disable_file_sink();
    Logger logger("test.logger", LogLevel::trace);

    REQUIRE_FALSE(Logger::is_file_sink_enabled());

    Logger::enable_file_sink(log_path.string(), false);
    REQUIRE(Logger::is_file_sink_enabled());

    logger(info)("Test {}", "message");

    Logger::disable_file_sink();

    const auto content = read_file(log_path);
    // fs::remove(log_path);

    INFO(content);
    REQUIRE_FALSE(content.empty());

    CHECK(content.find("\"name\":\"test.logger\"") != std::string::npos);
    CHECK(content.find("\"level\":\"info\"") != std::string::npos);
    CHECK(content.find("Test message") != std::string::npos);
    CHECK(content.find("test_logger.cpp") != std::string::npos);
}

TEST_CASE("Logger appends multiple entries")
{
    const auto log_path = make_unique_log_path();
    if (fs::exists(log_path))
    {
        fs::remove(log_path);
    }

    Logger::disable_file_sink();
    Logger logger("test.logger", LogLevel::trace);

    Logger::enable_file_sink(log_path.string(), false);

    logger(info)( "First {}", 1);
    logger(info)( "Second {}", 2);

    Logger::disable_file_sink();

    const auto content = read_file(log_path);
    // fs::remove(log_path);

    REQUIRE(content.find("First 1") != std::string::npos);
    REQUIRE(content.find("Second 2") != std::string::npos);

    const auto newline_count = static_cast<size_t>(std::count(content.begin(), content.end(), '\n'));
    CHECK(newline_count >= 2);
}
