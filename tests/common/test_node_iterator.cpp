#include <catch.hpp>
#include <common_node.hpp>
#include <vector>
#include <string>

using namespace ssp4cpp::common::graph;

TEST_CASE("Node iterator traverses node and direct children", "[Node][iterator]") {
    Node a("A"), b("B"), c("C");
    a.add_child(&b);
    a.add_child(&c);
    std::vector<std::string> names;
    for (auto it = a.begin(); it != a.end(); ++it) {
        names.push_back((*it)->name);
    }
    REQUIRE(names.size() == 3);
    REQUIRE(names[0] == "A");
    REQUIRE(names[1] == "B");
    REQUIRE(names[2] == "C");
}

TEST_CASE("Node recursive_iterator traverses all descendants in pre-order", "[Node][recursive_iterator]") {
    Node a("A"), b("B"), c("C"), d("D"), e("E");
    a.add_child(&b);
    a.add_child(&c);
    b.add_child(&d);
    c.add_child(&e);
    // Tree:
    //   A
    //  / \
    // B   C
    // |    |
    // D    E
    std::vector<std::string> rec_names;
    for (auto it = a.begin(); it != a.end(); ++it) {
        rec_names.push_back((*it)->name);
    }
    // begin()/end() is not recursive, should be [A, B, C]
    REQUIRE(rec_names.size() == 3);
    // Now test recursive traversal
    rec_names.clear();
    for (auto it = a.recursive_iterator(&a); it != a.recursive_iterator(nullptr); ++it) {
        rec_names.push_back((*it)->name);
    }
    std::vector<std::string> expected = {"A", "B", "D", "C", "E"};
    REQUIRE(rec_names == expected);
}
