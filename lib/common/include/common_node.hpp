#pragma once

#include "common_string.hpp"
#include "common_log.hpp"

#include <vector>
#include <algorithm>
#include <map>
#include <list>
#include <unordered_set>
#include <unordered_map>
#include <stack>

namespace ssp4cpp::common::graph
{

    class Node
    {
        Logger log = Logger("Node", LogLevel::ext_trace);

    public:
        std::string name;
        std::vector<Node *> children = {};
        std::vector<Node *> parents = {};

        /* === Constructors =================================================== */

        Node() : name("") {}

        explicit Node(std::string name) : name(std::move(name)) {}

        /**
         * Copy constructor (shallow): duplicates the Node object itself while
         * keeping *all* child/parent pointers identical to the original.
         */
        Node(const Node &other)
            : name(other.name),
              children(other.children),
              parents(other.parents)
        {
        }

        /* === Relationship management ======================================= */

        void add_child(Node *node)
        {
            if (!contains_child(node))
            {
                children.push_back(node);
                // keep bidirectional consistency
                node->add_parent(this);
            }
        }

        void add_parent(Node *node)
        {
            if (!contains_parent(node))
            {
                parents.push_back(node);
                // keep bidirectional consistency
                node->add_child(this);
            }
        }

        void remove_child(Node *node)
        {
            auto it = std::find(children.begin(), children.end(), node);
            if (it != children.end())
            {
                children.erase(it);
                node->remove_parent(this);
            }
        }

        void remove_parent(Node *node)
        {
            auto it = std::find(parents.begin(), parents.end(), node);
            if (it != parents.end())
            {
                parents.erase(it);
                node->remove_child(this);
            }
        }

        void replace_child(Node *from, Node *to)
        {
            if (this->contains_child(from))
            {
                remove_child(from);
                add_child(to);
            }
        }

        void replace_parent(Node *from, Node *to)
        {
            if (this->contains_parent(from))
            {
                remove_parent(from);
                add_parent(to);
            }
        }

        // replaces any matching child and parent
        void replace(Node *from, Node *to)
        {
            replace_child(from, to);
            replace_parent(from, to);
        }

        bool contains_child(Node *node) const
        {
            return std::find(children.begin(), children.end(), node) != children.end();
        }

        bool contains_parent(Node *node) const
        {
            return std::find(parents.begin(), parents.end(), node) != parents.end();
        }

        bool has_child() const { return !children.empty(); }

        bool has_parent() const { return !parents.empty(); }

        bool is_orphan() const { return !has_child() && !has_parent(); }

        int nr_children() const { return static_cast<int>(children.size()); }

        int nr_parents() const { return static_cast<int>(parents.size()); }

        friend std::ostream &operator<<(std::ostream &os, const Node &obj)
        {
            os << "Node { \n"
               << "name: " << obj.name << std::endl
               << "children: " << obj.children.size() << std::endl
               << "parents: " << obj.parents.size() << std::endl
               << " }" << std::endl;

            return os;
        }

        std::string to_string() const { return common::str::stream_to_str(*this); }

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

        // All nodes that lack parents
        std::vector<Node *> get_ancestors()
        {
            auto all_nodes = this->all_nodes();
            auto ancestors = Node::get_ancestors(all_nodes);
            return std::move(ancestors);
        }

        /* === Generic helpers ================================================= */

        template <typename T>
        static std::vector<Node *> cast_to_parent_ptrs(const std::vector<T *> &node)
        {
            std::vector<graph::Node *> node_ptrs(node.begin(), node.end());
            return node_ptrs;
        }

        // All nodes that lack parents
        template <typename T>
        static std::vector<T *> get_ancestors(const std::vector<T *> &nodes)
        {
            std::vector<T *> out;
            for (auto &n : nodes)
            {
                if (!n->has_parent())
                {
                    out.push_back(n);
                }
            }
            return out;
        }

        std::string to_dot() const
        {
            auto nodes = this->all_nodes();
            return Node::to_dot(nodes);
        }

        template <typename T>
        static std::string to_dot(const std::vector<T *> &nodes)
        {
            std::stringstream ss;
            ss << "digraph{" << std::endl;

            for (auto &node : nodes)
            {
                for (auto &c : node->children)
                {
                    ss << '\"' << node->name << "\" -> \"" << c->name << "\"\n";
                }
            }
            ss << "}" << std::endl;
            return ss.str();
        }

        template <typename T>
        static std::vector<T *> pop_orphans(std::vector<T *> nodes)
        {
            std::vector<T *> out;
            for (auto &n : nodes)
            {
                if (n->is_orphan())
                {
                    // log.ext_trace("[{}] Deleting {}", __func__, n->name);
                    delete n;
                }
                else
                {
                    out.push_back(n);
                }
            }
            return out;
        }

        /* === Copy helpers ==================================================== */

        /** Create a shallow copy of *this. */
        Node *shallow_copy() const { return new Node(*this); }

        /** Recursively duplicates the entire graph rooted at *this*. */
        Node *deep_copy() const
        {
            std::unordered_map<const Node *, Node *> map;

            auto nodes = this->all_nodes();

            for (auto &n : nodes)
            {
                Node *clone = n->shallow_copy();
                map[n] = clone;
            }

            for (auto &[_, new_node] : map)
            {
                for (auto [replace_old_node, replace_new_node] : map)
                {
                    new_node->replace(const_cast<Node *>(replace_old_node), replace_new_node);
                }
            }

            return map[this];
        }

        /** Static convenience wrappers */
        static Node *shallow_copy(const Node *root) { return root ? new Node(*root) : nullptr; }
        static Node *deep_copy(const Node *root) { return root ? root->deep_copy() : nullptr; }

        // Recursive iterator for Node and all descendants (pre-order traversal)
        class recursive_iterator
        {
            std::list<Node *> stack;

        public:
            using iterator_category = std::forward_iterator_tag;
            using value_type = Node *;
            using difference_type = std::ptrdiff_t;
            using pointer = Node **;
            using reference = Node *&;

            // set first element
            recursive_iterator(Node *root)
            {
                if (root)
                    stack.push_back(root);
            }

            // access current element
            Node *operator*() const
            {
                return stack.front();
            }

            recursive_iterator &operator++()
            {
                Node *current = stack.front();
                stack.pop_front();

                // Add the children of the removed item
                for (auto child : current->children)
                {
                    stack.push_back(child);
                }
                return *this;
            }

            bool operator!=(const recursive_iterator &other) const
            {
                return stack != other.stack;
            }
        };

        recursive_iterator begin() { return recursive_iterator(this); }
        recursive_iterator end() { return recursive_iterator(nullptr); }
    };
}
