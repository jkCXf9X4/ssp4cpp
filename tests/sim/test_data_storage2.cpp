#include <catch.hpp>

#include "FMI2_Enums.hpp"

#include "data_storage2.hpp"

#include <string>

using namespace ssp4cpp::sim;
using namespace ssp4cpp::sim::utils;

// A mock item type for testing
struct TestDataItem
{
    std::string name;
    DataType type;
};

TEST_CASE("DataStorage2 basic allocation", "[DataStorage2]")
{
    DataStorage2<TestDataItem> storage;

    TestDataItem item1{"var1", DataType::Integer};
    TestDataItem item2{"var2", DataType::Real};

    storage.add(item1);
    storage.add(item2);

    REQUIRE(storage.names.size() == 2);
    REQUIRE(storage.names[0] == "var1");
    REQUIRE(storage.names[1] == "var2");

    REQUIRE(storage.types.size() == 2);
    REQUIRE(storage.types[0] == DataType::Integer);
    REQUIRE(storage.types[1] == DataType::Real);

    REQUIRE(storage.positions.size() == 2);
    REQUIRE(storage.positions[0] == 0);
    REQUIRE(storage.positions[1] == get_data_type_size(DataType::Integer));

    REQUIRE(storage.pos == get_data_type_size(DataType::Integer) + get_data_type_size(DataType::Real));

    storage.allocate();

    REQUIRE(storage.locations.size() == 1);
    REQUIRE(storage.locations[0].size() == 2);
}

TEST_CASE("DataStorage2 multiple areas", "[DataStorage2]")
{
    DataStorage2<TestDataItem> storage(5);

    TestDataItem item1{"var1", DataType::Boolean};
    storage.add(item1);

    REQUIRE(storage.areas == 5);

    storage.allocate();

    REQUIRE(storage.locations.size() == 5);
    REQUIRE(storage.locations[0].size() == 1);
    REQUIRE(storage.locations[4].size() == 1);

    void *loc_area_0 = storage.locations[0][0];
    void *loc_area_4 = storage.locations[4][0];

    auto offset = reinterpret_cast<std::byte *>(loc_area_4) - reinterpret_cast<std::byte *>(loc_area_0);
    REQUIRE(offset == 4 * storage.pos);
}
