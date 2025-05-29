#pragma once

#include <vector>
#include <algorithm>
#include <map>
#include <list>
#include <unordered_set>
#include <stack>

namespace ssp4cpp::common::graph
{

    class Node
    {
    public:
        std::string name;
        std::vector<Node *> children = {};
        std::vector<Node *> parents = {};

        Node()
        {
            this->name = "";
        }

        Node(std::string name)
        {
            this->name = name;
        }

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
               << "name: " << obj.name << endl
               << "children: " << obj.children.size() << endl
               << "parents: " << obj.parents.size() << endl
               << " }" << endl;

            return os;
        }

        /** Return every node reachable through either child- or parent-links. */
        std::vector<Node *> all_nodes() const
        {
            std::vector<Node *> result;
            std::unordered_set<Node *> visited;

            std::stack<Node *> st;
            st.push(const_cast<Node *>(this)); // root

            while (!st.empty())
            {
                Node *cur = st.top();
                st.pop();

                if (!visited.insert(cur).second) // already seen
                    continue;

                result.push_back(cur);

                /* explore all outgoing and incoming arcs */
                for (Node *c : cur->children)
                    st.push(c);
                for (Node *p : cur->parents)
                    st.push(p);
            }
            return result;
        }

        std::string to_str()
        {
            return common::str::stream_to_str(*this);
        }

        template <typename T>
        static std::vector<Node *> cast_to_parent_ptrs(const std::vector<T *> &node)
        {
            std::vector<graph::Node *> node_ptrs(node.begin(), node.end());
            return node_ptrs;
        }

        std::string to_dot() const
        {
            auto nodes = this->all_nodes();
            return Node::to_dot(nodes);
        }

        static std::string to_dot(const vector<Node *> &nodes)
        {
            std::stringstream ss;
            ss << "digraph{" << std::endl;

            for (auto &node : nodes)
            {
                for (Node *c : node->children)
                {
                    ss << '"' << node->name << "\" -> \"" << c->name << "\"\n";
                }
            }
            ss << "}" << std::endl;
            return ss.str();
        }
    };
}