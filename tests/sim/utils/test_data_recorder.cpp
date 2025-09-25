#include <catch.hpp>
#include "common_log.hpp"

#include "common_time.hpp"
#include "utils/data_recorder.hpp"
#include "utils/data_type.hpp"

#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include <algorithm>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <thread>
#include <chrono>

using namespace ssp4cpp;
using namespace ssp4cpp::sim::utils;

// Helper function to check if file exists and contains expected data
bool check_file_contains(const std::string &filename, const std::string &expected)
{
    std::ifstream file(filename);
    if (!file.is_open())
        return false;

    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();

    return content.find(expected) != std::string::npos;
}

void remove_if_existing(std::string name)
{
    // Remove any existing test file
    if (std::filesystem::exists(name))
    {
        std::filesystem::remove(name);
    }
}

TEST_CASE("DataRecorder initialization and cleanup", "[DataRecorder]")
{
    // Use a temporary filename for testing
    std::string test_filename = "build/test_recorder_output.csv";
    remove_if_existing(test_filename);

    // Scope for the DataRecorder to ensure it's destructed properly
    {
        DataRecorder recorder(test_filename);
        // Check if file was created
        REQUIRE(std::filesystem::exists(test_filename));
    }

    // After destruction, file should still exist
    REQUIRE(std::filesystem::exists(test_filename));

    // Clean up the test file
    std::filesystem::remove(test_filename);
}

TEST_CASE("DataRecorder configures trackers and headers", "[DataRecorder]")
{
    const std::string test_filename = "build/test_recorder_headers.csv";
    remove_if_existing(test_filename);

    DataRecorder recorder(test_filename);

    DataStorage storage(2, "signals");
    storage.add("signals.real", DataType::real, 1);
    storage.add("signals.int", DataType::integer, 1);
    storage.allocate();

    recorder.add_storage(&storage);

    REQUIRE(recorder.trackers.size() == 1);
    REQUIRE(recorder.row_size == storage.pos);

    recorder.init();

    REQUIRE(recorder.updated_tracker.size() == recorder.rows);
    REQUIRE(recorder.updated_tracker.front().size() == recorder.trackers.size());

    recorder.file.flush();
    recorder.file.close();

    REQUIRE(check_file_contains(test_filename, "time,signals.real,signals.int"));

    std::filesystem::remove(test_filename);
}

TEST_CASE("DataRecorder writes new rows when storages provide data", "[DataRecorder]")
{
    const std::string test_filename = "build/test_recorder_rows.csv";
    remove_if_existing(test_filename);

    DataRecorder recorder(test_filename);

    DataStorage storage(2, "signals");
    storage.add("signals.temperature", DataType::real, 1);
    storage.add("signals.mode", DataType::integer, 0);
    storage.allocate();

    recorder.add_storage(&storage);
    recorder.init();
    recorder.start_recording();

    const std::size_t area = 0;
    const double temperature = 42.5;
    const int mode = 7;

    std::memcpy(storage.get_item(area, 0), &temperature, sizeof(double));
    std::memcpy(storage.get_item(area, 1), &mode, sizeof(int));

    const uint64_t timestamp = 1ULL * common::time::nanoseconds_per_second;
    storage.set_time(area, timestamp);
    storage.flag_new_data(area);

    recorder.update();
    std::this_thread::sleep_for(std::chrono::milliseconds(50));

    recorder.stop_recording();

    REQUIRE_FALSE(storage.new_data_flags[area]);
    REQUIRE(check_file_contains(test_filename, "1, 42.5"));
    REQUIRE(check_file_contains(test_filename, ", 7"));

    std::filesystem::remove(test_filename);
}

TEST_CASE("DataRecorder coalesces updates from multiple storages", "[DataRecorder]")
{
    const std::string test_filename = "build/test_recorder_multistorage.csv";
    remove_if_existing(test_filename);

    DataRecorder recorder(test_filename);

    DataStorage primary(2, "primary");
    primary.add("primary.temperature", DataType::real, 1);
    primary.add("primary.mode", DataType::integer, 0);
    primary.allocate();

    DataStorage secondary(2, "secondary");
    secondary.add("secondary.pressure", DataType::real, 1);
    secondary.add("secondary.index", DataType::integer, 2);
    secondary.allocate();

    recorder.add_storage(&primary);
    recorder.add_storage(&secondary);
    recorder.init();
    recorder.start_recording();

    constexpr std::size_t area = 0;
    const double primary_temp = 42.5;
    const int primary_mode = 7;
    const double secondary_pressure = 3.14;
    const int secondary_index = -2;

    std::memcpy(primary.get_item(area, 0), &primary_temp, sizeof(double));
    std::memcpy(primary.get_item(area, 1), &primary_mode, sizeof(int));
    std::memcpy(secondary.get_item(area, 0), &secondary_pressure, sizeof(double));
    std::memcpy(secondary.get_item(area, 1), &secondary_index, sizeof(int));

    const uint64_t timestamp = 1ULL * common::time::nanoseconds_per_second;
    primary.set_time(area, timestamp);
    secondary.set_time(area, timestamp);
    primary.flag_new_data(area);
    secondary.flag_new_data(area);

    recorder.update();
    std::this_thread::sleep_for(std::chrono::milliseconds(50));

    recorder.stop_recording();

    REQUIRE_FALSE(primary.new_data_flags[area]);
    REQUIRE_FALSE(secondary.new_data_flags[area]);

    std::ifstream file(test_filename);
    REQUIRE(file.is_open());

    std::vector<std::string> lines;
    std::string line;
    while (std::getline(file, line))
    {
        lines.push_back(line);
    }

    auto data_line = std::find_if(lines.begin(), lines.end(), [](const std::string &l)
                                  { return l.starts_with("1"); });
    REQUIRE(data_line != lines.end());
    REQUIRE(data_line->find("42.5") != std::string::npos);
    REQUIRE(data_line->find(", 7") != std::string::npos);
    REQUIRE(data_line->find("3.14") != std::string::npos);
    REQUIRE(data_line->find("-2") != std::string::npos);

    const auto occurrences_of_timestamp = std::count_if(lines.begin(), lines.end(), [](const std::string &l)
                                                        { return l.starts_with("1"); });
    REQUIRE(occurrences_of_timestamp == 1);

    std::filesystem::remove(test_filename);
}
