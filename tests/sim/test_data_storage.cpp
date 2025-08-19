#include <catch.hpp>

#include "FMI2_Enums.hpp"

#include "data_storage.hpp"

#include <string>

using namespace ssp4cpp::sim;
using namespace ssp4cpp::sim::utils;


TEST_CASE("DataStorage2 basic allocation", "[DataStorage2]")
{
    DataStorage storage;

    storage.add("var1", DataType::integer);
    storage.add("var2", DataType::real);

    storage.allocate();

    REQUIRE(storage.names.size() == 2);
    REQUIRE(storage.names[0] == "var1");
    REQUIRE(storage.names[1] == "var2");

    REQUIRE(storage.types.size() == 2);
    REQUIRE(storage.types[0] == DataType::integer);
    REQUIRE(storage.types[1] == DataType::real);

    REQUIRE(storage.positions.size() == 2);
    REQUIRE(storage.positions[0] == 0);
    REQUIRE(storage.positions[1] == get_data_type_size(DataType::integer));

    REQUIRE(storage.pos == get_data_type_size(DataType::integer) + get_data_type_size(DataType::real));

    REQUIRE(storage.locations.size() == 1);
    REQUIRE(storage.locations[0].size() == 2);
}

TEST_CASE("DataStorage2 multiple areas", "[DataStorage2]")
{
    DataStorage storage(5);

    storage.add("var1", DataType::boolean);

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
