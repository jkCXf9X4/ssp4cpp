#include <catch2/catch_test_macros.hpp>

#include "data_ring_storage.hpp"
#include "data_type.hpp"

using namespace ssp4cpp::sim;
using namespace ssp4cpp::sim::utils;

TEST_CASE("RingStorage constructor")
{
    SECTION("capacity 0 throws exception")
    {
        REQUIRE_THROWS_AS(RingStorage(0), std::runtime_error);
    }

    SECTION("capacity > 0")
    {
        RingStorage storage(10);
        REQUIRE(storage.access_counter == 0);
    }
}

TEST_CASE("RingStorage add and allocate")
{
    RingStorage storage(10);
    storage.add("test", DataType::real);
    storage.allocate();
}

TEST_CASE("RingStorage push")
{
    RingStorage storage(3);
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
    RingStorage storage(3);
    auto index = storage.add("test", DataType::integer);
    storage.allocate();

    auto area = storage.push(100);
    auto item = (int32_t*)storage.get_item(area, index);
    *item = 1;

    area = storage.push(200);
    item = (int32_t*)storage.get_item(area, index);
    *item = 2;

    area = storage.push(300);
    item = (int32_t*)storage.get_item(area, index);
    *item = 3;

    REQUIRE( *(int32_t*)storage.get_valid_item(100, index) == 1);
    REQUIRE( *(int32_t*)storage.get_valid_item(180, index) == 1);
    REQUIRE( *(int32_t*)storage.get_valid_item(201, index) == 2);

}

TEST_CASE("RingStorage get_valid_item")
{
    RingStorage storage(3);
    storage.add("test", DataType::real);
    storage.allocate();

    storage.push(100);
    storage.push(200);
    storage.push(300);

    REQUIRE(storage.get_valid_item(50, 0) == nullptr);
    REQUIRE(storage.get_valid_item(100, 0) != nullptr);
    REQUIRE(storage.get_valid_item(150, 0) != nullptr);
    REQUIRE(storage.get_valid_item(200, 0) != nullptr);
    REQUIRE(storage.get_valid_item(250, 0) != nullptr);
    REQUIRE(storage.get_valid_item(300, 0) != nullptr);
    REQUIRE(storage.get_valid_item(350, 0) != nullptr);
}