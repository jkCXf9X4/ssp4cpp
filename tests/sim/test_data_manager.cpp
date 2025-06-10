#include <catch.hpp>
#include "data/data_manager.hpp"
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include <cstdint>
#include <cstring>

using namespace ssp4cpp::sim::data;

struct TestStruct {
    int a;
    double b;
};

TEST_CASE("DataManager basic set/get", "[DataManager]") {
    DataManager mgr(5);
    size_t obj_size = sizeof(TestStruct);
    u_int64_t ref = mgr.initData(obj_size);

    TestStruct t1 = {42, 3.14};
    TestStruct t2 = {7, 2.71};

    mgr.setData(100, ref, &t1);
    mgr.setData(200, ref, &t2);

    // Should get t1 for time 150, t2 for time 250
    void* data1 = mgr.getData(150, ref);
    REQUIRE(data1 != nullptr);
    TestStruct* res1 = static_cast<TestStruct*>(data1);
    REQUIRE(res1->a == 42);
    REQUIRE_THAT(res1->b, Catch::Matchers::WithinAbs(3.14, 0.1));

    void* data2 = mgr.getData(250, ref);
    REQUIRE(data2 != nullptr);
    TestStruct* res2 = static_cast<TestStruct*>(data2);
    REQUIRE(res2->a == 7);
    REQUIRE_THAT(res1->b, Catch::Matchers::WithinAbs(2.71, 0.1));
}

TEST_CASE("DataManager returns nullptr for no valid data", "[DataManager]") {
    DataManager mgr(3);
    size_t obj_size = sizeof(TestStruct);
    u_int64_t ref = mgr.initData(obj_size);

    TestStruct t = {1, 1.0};
    // Insert at time 100
    mgr.setData(100, ref, &t);

    // Query before any data
    void* data = mgr.getData(50, ref);
    REQUIRE(data == nullptr);
}

TEST_CASE("DataManager buffer size limit", "[DataManager]") {
    DataManager mgr(2);
    size_t obj_size = sizeof(TestStruct);
    u_int64_t ref = mgr.initData(obj_size);

    TestStruct t1 = {1, 1.0};
    TestStruct t2 = {2, 2.0};
    TestStruct t3 = {3, 3.0};

    mgr.setData(100, ref, &t1); 
    mgr.setData(200, ref, &t2);
    mgr.setData(300, ref, &t3);

    // Only t2 and t3 should be in buffer
    void* data = mgr.getData(150, ref);
    REQUIRE(data == nullptr); // t1 should be evicted
    data = mgr.getData(250, ref);
    REQUIRE(data != nullptr);
    data = mgr.getData(350, ref);
    REQUIRE(data != nullptr);
}
