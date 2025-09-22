#include <catch.hpp>
#include "common_log.hpp"

#include "utils/data_recorder.hpp"
#include "utils/data_type.hpp"

#include <catch2/matchers/catch_matchers_floating_point.hpp>

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

