#include <catch2/catch_test_macros.hpp>

#include "common_log.hpp"

#include "data_ring_storage.hpp"
#include "data_type.hpp"

using namespace ssp4cpp::sim;
using namespace ssp4cpp::sim::utils;

ssp4cpp::common::Logger logger = ssp4cpp::common::Logger("RingStorage", ssp4cpp::common::LogLevel::debug);

TEST_CASE("RingStorage constructor")
{
    SECTION("capacity 0 throws exception")
    {
        REQUIRE_THROWS_AS(RingStorage(0, ""), std::runtime_error);
    }

    SECTION("capacity > 0")
    {
        RingStorage storage(10, "");
        REQUIRE(storage.access_counter == 0);
    }
}

TEST_CASE("RingStorage add and allocate")
{
    RingStorage storage(10, "");
    storage.add("test", DataType::real);
    storage.allocate();
}

TEST_CASE("RingStorage push empty")
{
    RingStorage storage(3, "");
    storage.allocate();

    auto area = storage.push(2);
    // std::cout << "Area:" << area << std::endl;
    storage.flag_new_data(area);
}

TEST_CASE("RingStorage push")
{
    RingStorage storage(3, "");
    storage.add("test", DataType::real);
    storage.allocate();

    storage.push(100);
    REQUIRE(storage.access_counter == 1);

    storage.push(200);
    REQUIRE(storage.access_counter == 2);

    storage.push(300);
    REQUIRE(storage.access_counter == 3);

    storage.push(400);
    REQUIRE(storage.access_counter == 4);

    std::cout << storage << std::endl;
}

TEST_CASE("RingStorage get_item")
{
    RingStorage storage(2, "");
    auto index = storage.add("test", DataType::integer);
    storage.allocate();

    auto area1 = storage.push(100);
    logger.trace("Pushing 100, area: {}", area1);
    auto item = (int32_t*)storage.get_item(area1, index);
    *item = 1;
    storage.flag_new_data(area1);
    
    auto area2 = storage.push(200);
    logger.trace("Pushing 200, area: {}", area2);
    item = (int32_t*)storage.get_item(area2, index);
    *item = 2;
    storage.flag_new_data(area2);
    
    auto area3 = storage.push(300);
    logger.trace("Pushing 300, area: {}", area3);
    item = (int32_t*)storage.get_item(area3, index);
    *item = 3;
    storage.flag_new_data(area3);

    // no valid for 100 anymore
    REQUIRE( storage.get_valid_item(100, index) == nullptr);

    REQUIRE( *(int32_t*)storage.get_valid_item(201, index) == 2);
    REQUIRE( *(int32_t*)storage.get_valid_item(301, index) == 3);

}

TEST_CASE("RingStorage get_valid_item")
{
    RingStorage storage(2, "");
    storage.add("test", DataType::real);
    storage.allocate();

    storage.push(100);
    storage.push(200);
    // overwrite the first
    storage.push(300);

    REQUIRE(storage.get_valid_item(50, 0) == nullptr);
    REQUIRE(storage.get_valid_item(100, 0) == nullptr);
    REQUIRE(storage.get_valid_item(150, 0) == nullptr);
    REQUIRE(storage.get_valid_item(200, 0) != nullptr);
    REQUIRE(storage.get_valid_item(250, 0) != nullptr);
    REQUIRE(storage.get_valid_item(300, 0) != nullptr);
    REQUIRE(storage.get_valid_item(350, 0) != nullptr);
}