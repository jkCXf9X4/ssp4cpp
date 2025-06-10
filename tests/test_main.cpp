#define CATCH_CONFIG_MAIN
#include <catch.hpp>

// This file provides the main() entry point for Catch2 tests.


class test
{
    vector<int> items;

    test()
    {
        items = get();
    }

    vector<int> get()
    {
        vector<int> a;
        a.push_back(6);
        return std::move(a);
    }
}


TEST_CASE("Test", "[test]")
{


}