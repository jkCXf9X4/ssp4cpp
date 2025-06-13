

#include <catch.hpp>
#include <common_node.hpp>

using namespace ssp4cpp::common::graph;

TEST_CASE("Node basic construction and name", "[Node]") {
    Node n1;
    REQUIRE(n1.name == "");
    Node n2("A");
    REQUIRE(n2.name == "A");
}

TEST_CASE("Node add_child and add_parent", "[Node]") {
    Node a("A"), b("B");
    a.add_child(&b);
    REQUIRE(a.children.size() == 1);
    REQUIRE(a.children[0] == &b);
    REQUIRE(b.parents.size() == 1);
    REQUIRE(b.parents[0] == &a);
}

TEST_CASE("Node remove_child and remove_parent", "[Node]") {
    Node a("A"), b("B");
    a.add_child(&b);
    a.remove_child(&b);
    REQUIRE(a.children.empty());
    REQUIRE(b.parents.empty());
}

TEST_CASE("Node replace_child and replace_parent", "[Node]") {
    Node a("A"), b("B"), c("C");
    a.add_child(&b);
    a.replace_child(&b, &c);
    REQUIRE(a.children.size() == 1);
    REQUIRE(a.children[0] == &c);
    c.replace_parent(&a, &b);
    REQUIRE(c.parents.size() == 1);
    REQUIRE(c.parents[0] == &b);
}

TEST_CASE("Node contains_child/parent, has_child/parent, is_orphan", "[Node]") {
    Node a("A"), b("B");
    REQUIRE(!a.has_child());
    REQUIRE(!a.has_parent());
    REQUIRE(a.is_orphan());
    a.add_child(&b);
    REQUIRE(a.has_child());
    REQUIRE(!a.is_orphan());
    REQUIRE(b.has_parent());
}

TEST_CASE("Node all_nodes and get_ancestors", "[Node]") {
    Node a("A"), b("B"), c("C");
    a.add_child(&b);
    b.add_child(&c);
    auto all = b.all_nodes();
    REQUIRE(all.size() == 3);
    auto ancestors = b.get_ancestors();
    REQUIRE(ancestors.size() == 1);
    REQUIRE(ancestors[0]->name == "A");
}

TEST_CASE("Node shallow_copy and deep_copy", "[Node]") {
    Node a("A"), b("B");
    a.add_child(&b);
    Node* shallow = a.shallow_copy();
    REQUIRE(shallow->name == "A");
    REQUIRE(shallow->children.size() == 1);
    delete shallow;
    Node* deep = a.deep_copy();
    REQUIRE(deep->name == "A");
    REQUIRE(deep->children.size() == 1);
    REQUIRE(deep->children[0]->name == "B");

    REQUIRE(&a != deep);

    delete deep->children[0];
    delete deep;
}

TEST_CASE("Node to_dot output", "[Node]") {
    Node a("A"), b("B");
    a.add_child(&b);
    std::string dot = a.to_dot();
    REQUIRE(dot.find("A\" -> \"B") != std::string::npos);
}
