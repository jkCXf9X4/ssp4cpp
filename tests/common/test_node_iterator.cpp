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
    for (auto node : a) {
        names.push_back(node->name);
    }
    REQUIRE(names.size() == 3);

    std::vector<std::string> expected = {"A", "B", "C"};
    REQUIRE(names == expected);

}

TEST_CASE("Node pointer iterator traverses node", "[Node][iterator]") {
    auto a = new Node("A");
    auto b = new Node("B");
    auto c = new Node("C");
    a->add_child(b);
    a->add_child(c);
    std::vector<std::string> names;
    for (auto node : *a) {
        names.push_back(node->name);
    }
    REQUIRE(names.size() == 3);

    std::vector<std::string> expected = {"A", "B", "C"};
    REQUIRE(names == expected);

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

    for (auto node : a) {
        rec_names.push_back(node->name);
    }
    std::vector<std::string> expected = {"A", "B", "C", "D", "E"};
    REQUIRE(rec_names == expected);
}
