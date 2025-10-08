#pragma once

#include "common_string.hpp"
#include "common_log.hpp"

#include <vector>
#include <string>
#include <list>
#include <stack>

namespace ssp4cpp::common::graph
{

    /**
     * @brief Basic bidirectional graph node used throughout the project.
     */
    class Node : public virtual str::IString
    {
        Logger log = Logger("ssp4cpp.common.Node", LogLevel::ext_trace);

    public:
        std::string name;
        std::vector<Node *> children = {};
        std::vector<Node *> parents = {};

        /* === Constructors =================================================== */

        Node();

        Node(std::string name);

        /**
         * Copy constructor (shallow): duplicates the Node object itself while
         * keeping *all* child/parent pointers identical to the original.
         */
        Node(const Node &other);

        virtual void print(std::ostream &os) const
        {
            os << "Node { \n"
               << "name: " << name << "\n"
               << "children: " << children.size() << "\n"
               << "parents: " << parents.size() << "\n"
               << " }" << "\n";
        }

        /* === Relationship management ======================================= */

        void add_child(Node *node);

        void add_parent(Node *node);

        void remove_child(Node *node);

        void remove_parent(Node *node);

        void replace_child(Node *from, Node *to);

        void replace_parent(Node *from, Node *to);

        // replaces any matching child and parent
        void replace(Node *from, Node *to);

        bool contains_child(Node *node) const;

        bool contains_parent(Node *node) const;

        bool has_child() const;

        bool has_parent() const;

        bool is_orphan() const;

        int nr_children() const;

        int nr_parents() const;

        /**
         * @brief Return every node reachable through either child or parent
         *        links starting from this node.
         */
        std::vector<Node *> all_nodes() const;

        // All nodes that lack parents
        std::vector<Node *> get_ancestors();

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

        std::string to_dot() const;

        template <typename T>
        static std::string to_dot(const std::vector<T *> &nodes)
        {
            std::stringstream ss;
            ss << "digraph{\n";

            for (auto &node : nodes)
            {
                for (auto &c : node->children)
                {
                    ss << '\"' << node->name << "\" -> \"" << c->name << "\"\n";
                }
            }
            ss << "}\n";
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
        /**
         * @brief Create a shallow copy of this node.
         *
         * Only the node itself is duplicated, child and parent pointers
         * still reference the same nodes as the original.
         */
        Node *shallow_copy() const;

        /**
         * @brief Recursively duplicate the entire graph rooted at this node.
         */
        Node *deep_copy() const;

        /** Static convenience wrappers */
        static Node *shallow_copy(const Node *root);
        static Node *deep_copy(const Node *root);

        /**
         * @brief Recursive iterator for Node and all descendants (pre-order traversal).
         */
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

        /** @brief Iterator to the first node in a recursive traversal. */
        recursive_iterator begin() { return recursive_iterator(this); }
        /** @brief End iterator for recursive traversal. */
        recursive_iterator end() { return recursive_iterator(nullptr); }
    };
}
