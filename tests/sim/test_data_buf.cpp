#include <catch.hpp>

#include "handler/data_buffer.hpp"

#include <cstdint>
#include <cstring>

using namespace ssp4cpp::sim::handler;

TEST_CASE("DataBuffer basic push and get", "[DataBuffer]") {
    DataBuffer buf(3, DataType::Integer, 0, "");
    int v1 = 10, v2 = 20, v3 = 30, v4 = 40;
    buf.push(&v1, 100);
    buf.push(&v2, 200);
    buf.push(&v3, 300);
    // Buffer is now full, next push will overwrite oldest
    buf.push(&v4, 400);
    // v1 should be overwritten, v2 should be at tail
    int pos;
    REQUIRE(buf.size == 3);
    REQUIRE(buf.get_time(0, pos) == 200);
    REQUIRE(*(int*)buf.data_ptr(pos) == 20);
    REQUIRE(buf.get_time(1, pos) == 300);
    REQUIRE(*(int*)buf.data_ptr(pos) == 30);
    REQUIRE(buf.get_time(2, pos) == 400);
    REQUIRE(*(int*)buf.data_ptr(pos) == 40);
}

TEST_CASE("DataBuffer get_valid returns correct element", "[DataBuffer]") {
    DataBuffer buf(3, DataType::Integer, 0, "");
    int v1 = 1, v2 = 2, v3 = 3;
    buf.push(&v1, 100);
    buf.push(&v2, 200);
    buf.push(&v3, 300);

    // get_valid should return the most recent element not newer than the given time
    int* res = (int*)buf.get_valid(250);
    REQUIRE(res != nullptr);
    REQUIRE(*res == 2);

    res = (int*)buf.get_valid(100);
    REQUIRE(res != nullptr);
    REQUIRE(*res == 1);

    res = (int*)buf.get_valid(50);
    REQUIRE(res == nullptr);
}

TEST_CASE("DataBuffer handles string type", "[DataBuffer][STRING]") {
    DataBuffer buf(2, DataType::String, 0, "");
    const char* s1 = "hello";
    const char* s2 = "world";
    buf.push((void*)s1, 100);
    buf.push((void*)s2, 200);
    // int pos;
    // void* d1 = buf.data_ptr(0)
    const char* d1 = static_cast<const char*>(buf.data_ptr(0));
    REQUIRE(strcmp(d1, "hello") == 0 );

    const char* d2 = static_cast<const char*>(buf.data_ptr(1));
    REQUIRE(strcmp(d2, "world") == 0 );
    
    const char* d3 = static_cast<const char*>(buf.get_valid(150));
    REQUIRE(strcmp(d3, "hello") == 0 );
}

TEST_CASE("DataBuffer is_empty and is_full", "[DataBuffer]") {
    DataBuffer buf(2, DataType::Integer, 0, "");
    int v = 1;
    REQUIRE(buf.is_empty());
    buf.push(&v, 1);
    REQUIRE(!buf.is_empty());
    buf.push(&v, 2);
    REQUIRE(buf.is_full());
}
