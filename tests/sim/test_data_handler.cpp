
#include <catch.hpp>
#include "common_log.hpp"

#include "data_handler.hpp"


#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include <cstdint>
#include <cstring>
#include <iostream>

using namespace ssp4cpp;
using namespace ssp4cpp::sim::handler;



TEST_CASE("DataHandler handles BOOL type", "[DataHandler][BOOL]")
{
    common::Logger log = common::Logger("TestDataHandler", common::LogLevel::ext_trace);
    log.ext_trace("[{}] init", __func__);
    DataHandler mgr(3, "test_output/test_bool.csv");
    uint64_t ref = mgr.initData(DataType::BOOL);

    bool v1 = true;
    bool v2 = false;
    log.ext_trace("[{}] set data", __func__);
    mgr.setData(100, ref, &v1);
    mgr.setData(200, ref, &v2);
    
    log.ext_trace("[{}] get data 1", __func__);
    void *data1 = mgr.getData(150, ref);
    REQUIRE(data1 != nullptr);
    REQUIRE(*static_cast<bool *>(data1) == true);
    
    log.ext_trace("[{}] get data 2", __func__);
    void *data2 = mgr.getData(250, ref);
    log.ext_trace("[{}] get data 2 after", __func__);
    REQUIRE(data2 != nullptr);
    REQUIRE(*static_cast<bool *>(data2) == false);
    log.ext_trace("[{}] complete", __func__);
}

TEST_CASE("DataHandler handles INT type", "[DataHandler][INT]")
{
    DataHandler mgr(3, "test_output/test_int.csv");
    uint64_t ref = mgr.initData(DataType::INT);

    int v1 = 42;
    int v2 = -7;
    mgr.setData(100, ref, &v1);
    mgr.setData(200, ref, &v2);

    void *data1 = mgr.getData(150, ref);
    REQUIRE(data1 != nullptr);
    REQUIRE(*static_cast<int *>(data1) == 42);

    void *data2 = mgr.getData(250, ref);
    REQUIRE(data2 != nullptr);
    REQUIRE(*static_cast<int *>(data2) == -7);
}

TEST_CASE("DataHandler handles REAL type", "[DataHandler][REAL]")
{
    DataHandler mgr(3, "test_output/test_real.csv");
    uint64_t ref = mgr.initData(DataType::REAL);

    double v1 = 3.14;
    double v2 = 2.71;
    mgr.setData(100, ref, &v1);
    mgr.setData(200, ref, &v2);

    void *data1 = mgr.getData(150, ref);
    REQUIRE(data1 != nullptr);
    REQUIRE_THAT(*static_cast<double *>(data1), Catch::Matchers::WithinAbs(3.14, 0.01));

    void *data2 = mgr.getData(250, ref);
    REQUIRE(data2 != nullptr);
    REQUIRE_THAT(*static_cast<double *>(data2), Catch::Matchers::WithinAbs(2.71, 0.01));
}

TEST_CASE("DataHandler handles STRING type", "[DataHandler][STRING]")
{
    DataHandler mgr(3, "test_output/test_string.csv");
    uint64_t ref = mgr.initData(DataType::STRING);

    std::string v1 = "foo";
    std::string v2 = "bar";
    mgr.setData(100, ref, &v1);
    mgr.setData(200, ref, &v2);

    void *data1 = mgr.getData(150, ref);
    REQUIRE(data1 != nullptr);
    REQUIRE(*static_cast<std::string *>(data1) == "foo");

    void *data2 = mgr.getData(250, ref);
    REQUIRE(data2 != nullptr);
    REQUIRE(*static_cast<std::string *>(data2) == "bar");
}

TEST_CASE("DataHandler handles ENUM type", "[DataHandler][ENUM]")
{
    DataHandler mgr(3, "test_output/test_enum.csv");
    uint64_t ref = mgr.initData(DataType::ENUM);

    int v1 = 1; // enums stored as int
    int v2 = 2;
    mgr.setData(100, ref, &v1);
    mgr.setData(200, ref, &v2);

    void *data1 = mgr.getData(150, ref);
    REQUIRE(data1 != nullptr);
    REQUIRE(*static_cast<int *>(data1) == 1);

    void *data2 = mgr.getData(250, ref);
    REQUIRE(data2 != nullptr);
    REQUIRE(*static_cast<int *>(data2) == 2);
}


struct TestStruct
{
    int a;
    double b;
};

TEST_CASE("DataHandler basic set/get", "[DataHandler]")
{
    DataHandler mgr(5, "test_output/test1.csv");
    size_t obj_size = sizeof(TestStruct);
    u_int64_t ref = mgr.initData(obj_size);

    TestStruct t1 = {42, 3.14};
    TestStruct t2 = {7, 2.71};

    mgr.setData(100, ref, &t1);
    mgr.setData(200, ref, &t2);

    // Should get t1 for time 150, t2 for time 250
    void *data1 = mgr.getData(150, ref);
    REQUIRE(data1 != nullptr);
    TestStruct *res1 = static_cast<TestStruct *>(data1);
    REQUIRE(res1->a == 42);
    REQUIRE_THAT(res1->b, Catch::Matchers::WithinAbs(3.14, 0.1));

    void *data2 = mgr.getData(250, ref);
    REQUIRE(data2 != nullptr);
    TestStruct *res2 = static_cast<TestStruct *>(data2);
    REQUIRE(res2->a == 7);
    REQUIRE_THAT(res2->b, Catch::Matchers::WithinAbs(2.71, 0.1));
}

TEST_CASE("DataHandler returns nullptr for no valid data", "[DataHandler]")
{
    DataHandler mgr(3, "test_output/test2.csv");
    size_t obj_size = sizeof(TestStruct);
    u_int64_t ref = mgr.initData(obj_size);

    TestStruct t = {1, 1.0};
    // Insert at time 100
    mgr.setData(100, ref, &t);

    // Query before any data
    void *data = mgr.getData(50, ref);
    REQUIRE(data == nullptr);
}

TEST_CASE("DataHandler buffer size limit", "[DataHandler]")
{
    DataHandler mgr(2, "test_output/test3.csv");
    size_t obj_size = sizeof(TestStruct);
    u_int64_t ref = mgr.initData(obj_size);

    TestStruct t1 = {1, 1.0};
    TestStruct t2 = {2, 2.0};
    TestStruct t3 = {3, 3.0};

    mgr.setData(100, ref, &t1);
    mgr.setData(200, ref, &t2);
    mgr.setData(300, ref, &t3);

    // Only t2 and t3 should be in buffer
    void *data = mgr.getData(150, ref);
    REQUIRE(data == nullptr); // t1 should be evicted
    data = mgr.getData(250, ref);
    REQUIRE(data != nullptr);
    data = mgr.getData(350, ref);
    REQUIRE(data != nullptr);
}
