
#include <catch2/catch_test_macros.hpp>

#include "utils/config.hpp"
#include <fstream>

using namespace ssp4cpp::sim::utils;

TEST_CASE("Config tests", "[config]")
{
    std::string config_file = "./tests/references/test_config.json";
    std::string malformed_config_file = "./tests/references/malformed_test_config.json";

    SECTION("Load from file")
    {
        REQUIRE_NOTHROW(Config::loadFromFile(config_file));
    }

    SECTION("Load from non-existent file")
    {
        REQUIRE_THROWS(Config::loadFromFile("non_existent_file.json"));
    }

    SECTION("Load from malformed file")
    {
        REQUIRE_THROWS(Config::loadFromFile(malformed_config_file));
    }

    // Load the config for the following tests
    Config::loadFromFile(config_file);

    SECTION("Get required value")
    {
        REQUIRE(Config::get<std::string>("name") == "test");
        REQUIRE(Config::get<int>("value") == 123);
        REQUIRE(Config::get<std::string>("nested.key") == "value");
        REQUIRE(Config::get<std::string>("array.0") == "a");
    }

    SECTION("Get required value that does not exist")
    {
        REQUIRE_THROWS(Config::get<std::string>("non_existent_key"));
    }

    SECTION("Get required value with type mismatch")
    {
        REQUIRE_THROWS(Config::get<int>("name"));
    }

    SECTION("Get with default value")
    {
        REQUIRE(Config::getOr<std::string>("name", "default") == "test");
        REQUIRE(Config::getOr<int>("value", 456) == 123);
        REQUIRE(Config::getOr<std::string>("nested.key", "default") == "value");
        REQUIRE(Config::getOr<std::string>("array.0", "default") == "a");
    }

    SECTION("Get with default value that does not exist")
    {
        REQUIRE(Config::getOr<std::string>("non_existent_key", "default") == "default");
    }

    SECTION("Get with default value with type mismatch")
    {
        REQUIRE_THROWS(Config::getOr<int>("name", 456));
    }

    SECTION("Resolve path")
    {
        REQUIRE(Config::resolvePath("name") != nullptr);
        REQUIRE(Config::resolvePath("nested.key") != nullptr);
        REQUIRE(Config::resolvePath("array.0") != nullptr);
        REQUIRE(Config::resolvePath("non_existent_key") == nullptr);
    }

}
