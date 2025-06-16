#include <catch.hpp>
#include "common_log.hpp"

#include "data_recorder.hpp"
#include "data_buffer.hpp"
#include "data_type.hpp"

#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include <cstdint>
#include <cstring>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <thread>
#include <chrono>

using namespace ssp4cpp;
using namespace ssp4cpp::sim::handler;

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

// Custom DataBuffer class for testing purposes
class TestDataBuffer : public DataBuffer
{
public:
    uint64_t data_reference = 42; // Default test reference id

    TestDataBuffer(DataType type)
        : DataBuffer(5, type, 42, "test_buffer")
    {
    }
};

TEST_CASE("DataRecorder initialization and cleanup", "[DataRecorder]")
{
    // Use a temporary filename for testing
    std::string test_filename = "tests/references/test_recorder_output.csv";
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

TEST_CASE("DataRecorder can register buffers", "[DataRecorder]")
{
    std::string test_filename = "tests/references/test_recorder_buffers.csv";
    remove_if_existing(test_filename);

    DataRecorder recorder(test_filename);
    TestDataBuffer buffer(DataType::INT);

    // Register the buffer
    recorder.register_buffer(&buffer);

    // Check if the buffer was registered by checking the internal buffers vector
    REQUIRE(recorder.buffers.size() == 1);
    REQUIRE(recorder.buffers[0].buffer == &buffer);

    // Clean up the test file
    std::filesystem::remove(test_filename);
}

TEST_CASE("DataRecorder callbacks work correctly", "[DataRecorder]")
{
    std::string test_filename = "tests/references/test_recorder_callbacks.csv";
    remove_if_existing(test_filename);

    DataRecorder recorder(test_filename);
    TestDataBuffer buffer(DataType::INT);

    // Get callbacks
    auto register_callback = recorder.get_register_buffer_callback();
    auto update_callback = recorder.get_update_callback();

    // Use callbacks
    register_callback(&buffer);

    // Check if buffer was registered
    REQUIRE(recorder.buffers.size() == 1);
    REQUIRE(recorder.buffers[0].buffer == &buffer);

    int a = 5;
    int b = 10;
    int c = 20;
    buffer.push(&a, 100);
    update_callback();
    buffer.push(&b, 120);
    update_callback();
    buffer.push(&c, 150);

    update_callback();

    usleep(500); // keep the recorder alive 
}

TEST_CASE("DataRecorder record function writes data to file", "[DataRecorder]")
{
    std::string test_filename = "tests/references/test_recorder_data.csv";
    remove_if_existing(test_filename);

    DataRecorder recorder(test_filename);

    // Test with different data types
    SECTION("BOOL data type")
    {
        bool value = true;
        recorder.record(1000, 1, DataType::BOOL, &value);

        // Check if "1000,1,1" appears in the file
        REQUIRE(check_file_contains(test_filename, "1000,1,1"));

        bool value2 = false;
        recorder.record(2000, 2, DataType::BOOL, &value2);

        // Check if "2000,2,0" appears in the file
        REQUIRE(check_file_contains(test_filename, "2000,2,0"));
    }

    SECTION("INT data type")
    {
        int value = 42;
        recorder.record(1000, 3, DataType::INT, &value);

        // Check if "1000,3,42" appears in the file
        REQUIRE(check_file_contains(test_filename, "1000,3,42"));
    }

    SECTION("REAL data type")
    {
        double value = 3.14159;
        recorder.record(1000, 4, DataType::REAL, &value);

        // Check if "1000,4,3.14159" appears in the file (note: precision may vary)
        REQUIRE(check_file_contains(test_filename, "1000,4,3.14159"));
    }

    SECTION("STRING data type")
    {
        std::string value = "test_string";
        recorder.record(1000, 5, DataType::STRING, &value);

        // Check if "1000,5,test_string" appears in the file
        REQUIRE(check_file_contains(test_filename, "1000,5,test_string"));
    }

    SECTION("UNKNOWN data type")
    {
        char value[] = {0x01, 0x02, 0x03};
        recorder.record(1000, 6, DataType::UNKNOWN, value);

        // Check if "1000,6,<bin>" appears in the file
        REQUIRE(check_file_contains(test_filename, "1000,6,<bin>"));
    }

}

TEST_CASE("DataRecorder update mechanism", "[DataRecorder]")
{
    std::string test_filename = "test_recorder_update.csv";
    remove_if_existing(test_filename);

    DataRecorder recorder(test_filename);

    // Call update and make sure it doesn't crash
    recorder.update();

    // Clean up the test file
    std::filesystem::remove(test_filename);
}