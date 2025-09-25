#include <catch.hpp>

#include "FMI2_Enums.hpp"
#include "FMI2_Enums_Ext.hpp"

#include "data_storage.hpp"

#include <string>

using namespace ssp4cpp::sim;
using namespace ssp4cpp::sim::utils;


TEST_CASE("DataStorage2 basic allocation", "[DataStorage2]")
{
    DataStorage storage(1);

    storage.add("var1", DataType::integer, 2);
    storage.add("var2", DataType::real, 1);

    storage.allocate();

    REQUIRE(storage.names.size() == 2);
    REQUIRE(storage.names[0] == "var1");
    REQUIRE(storage.names[1] == "var2");

    REQUIRE(storage.types.size() == 2);
    REQUIRE(storage.types[0] == DataType::integer);
    REQUIRE(storage.types[1] == DataType::real);

    REQUIRE(storage.positions.size() == 2);
    REQUIRE(storage.positions[0] == 0);
    REQUIRE(storage.positions[1] == ssp4cpp::fmi2::ext::enums::get_data_type_size(DataType::integer));

    REQUIRE(storage.pos == ssp4cpp::fmi2::ext::enums::get_data_type_size(DataType::integer) + ssp4cpp::fmi2::ext::enums::get_data_type_size(DataType::real));

    REQUIRE(storage.locations.size() == 1);
    REQUIRE(storage.locations[0].size() == 2);

    std::cout << storage.to_string() << std::endl;
}

TEST_CASE("DataStorage2 multiple areas", "[DataStorage2]")
{
    DataStorage storage(5);

    storage.add("var1", DataType::boolean, 0);

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

TEST_CASE("DataStorage stores derivatives per area", "[DataStorage2]")
{
    DataStorage storage(3);

    auto index = storage.add("der_real", DataType::real, 3);

    storage.allocate();

    REQUIRE(storage.der_positions.size() == storage.positions.size());
    REQUIRE(storage.der_positions[index] == 0);

    auto first_area_first_order = storage.get_derivative(0, index, 1);
    auto first_area_second_order = storage.get_derivative(0, index, 2);
    auto last_area_first_order = storage.get_derivative(2, index, 1);

    REQUIRE(first_area_first_order != nullptr);
    REQUIRE(first_area_second_order != nullptr);
    REQUIRE(last_area_first_order != nullptr);
    REQUIRE(first_area_first_order != first_area_second_order);
    REQUIRE(first_area_first_order != last_area_first_order);

    *reinterpret_cast<double *>(first_area_first_order) = 1.5;
    *reinterpret_cast<double *>(first_area_second_order) = -0.25;
    *reinterpret_cast<double *>(last_area_first_order) = 3.75;

    REQUIRE(*reinterpret_cast<double *>(storage.get_derivative(0, index, 1)) == Catch::Approx(1.5));
    REQUIRE(*reinterpret_cast<double *>(storage.get_derivative(0, index, 2)) == Catch::Approx(-0.25));
    REQUIRE(*reinterpret_cast<double *>(storage.get_derivative(2, index, 1)) == Catch::Approx(3.75));

    auto stride = reinterpret_cast<std::byte *>(first_area_second_order) - reinterpret_cast<std::byte *>(first_area_first_order);
    REQUIRE(stride == static_cast<std::ptrdiff_t>(sizeof(double)));
}
