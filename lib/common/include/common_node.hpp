#pragma once

#include <vector>
#include <algorithm>
#include <map>
#include <list>

namespace ssp4cpp::common::graph
{

    class Node
    {

        std::vector<Node *> children = {};
        std::vector<Node *> parents = {};
    public:
        Node() {}

        void add_child(Node *node)
        {
            children.push_back(node);
            node->add_parent(this);
        }

        void add_parent(Node *node)
        {
            parents.push_back(node);
        }

        bool contains_child(Node *node)
        {
            return std::find(children.begin(), children.end(), node) != children.end();
        }

        bool contains_parent(Node *node)
        {
            return std::find(parents.begin(), parents.end(), node) != parents.end();
        }

        bool has_child()
        {
            return children.empty() != true;
        }

        bool has_parent()
        {
            return parents.empty() != true;
        }

        int nr_children()
        {
            return children.size();
        }

        int nr_parents()
        {
            return parents.size();
        }

        friend ostream &operator<<(ostream &os, const Node &obj)
        {
            os << "Node { \n"
               << "children: " << obj.children.size() << endl
               << "parents: " << obj.parents.size() << endl
               << " }" << endl;

            return os;
        }

        std::string to_str()
        {
            return common::str::stream_to_str(*this);
        }
    };
}