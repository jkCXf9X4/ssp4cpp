

#include "common_node.hpp"

#include <map>
#include <unordered_set>
#include <unordered_map>

namespace ssp4cpp::common::graph
{

    Node::Node() : name("") {}

    Node::Node(std::string name) : name(std::move(name)) {}

    Node::Node(const Node &other)
        : name(other.name),
          children(other.children),
          parents(other.parents)
    {
    }

    /* === Relationship management ======================================= */

    void Node::add_child(Node *node)
    {
        if (!contains_child(node))
        {
            children.push_back(node);
            // keep bidirectional consistency
            node->add_parent(this);
        }
    }

    void Node::add_parent(Node *node)
    {
        if (!contains_parent(node))
        {
            parents.push_back(node);
            // keep bidirectional consistency
            node->add_child(this);
        }
    }

    void Node::remove_child(Node *node)
    {
        auto it = std::find(children.begin(), children.end(), node);
        if (it != children.end())
        {
            children.erase(it);
            node->remove_parent(this);
        }
    }

    void Node::remove_parent(Node *node)
    {
        auto it = std::find(parents.begin(), parents.end(), node);
        if (it != parents.end())
        {
            parents.erase(it);
            node->remove_child(this);
        }
    }

    void Node::replace_child(Node *from, Node *to)
    {
        if (this->contains_child(from))
        {
            remove_child(from);
            add_child(to);
        }
    }

    void Node::replace_parent(Node *from, Node *to)
    {
        if (this->contains_parent(from))
        {
            remove_parent(from);
            add_parent(to);
        }
    }

    // replaces any matching child and parent
    void Node::replace(Node *from, Node *to)
    {
        replace_child(from, to);
        replace_parent(from, to);
    }

    bool Node::contains_child(Node *node) const
    {
        return std::find(children.begin(), children.end(), node) != children.end();
    }

    bool Node::contains_parent(Node *node) const
    {
        return std::find(parents.begin(), parents.end(), node) != parents.end();
    }

    bool Node::has_child() const { return !children.empty(); }

    bool Node::has_parent() const { return !parents.empty(); }

    bool Node::is_orphan() const { return !has_child() && !has_parent(); }

    int Node::nr_children() const { return static_cast<int>(children.size()); }

    int Node::nr_parents() const { return static_cast<int>(parents.size()); }

    std::string Node::to_string() const { return common::str::stream_to_str(*this); }

    std::vector<Node *> Node::all_nodes() const
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

    std::vector<Node *> Node::get_ancestors()
    {
        auto all_nodes = this->all_nodes();
        auto ancestors = Node::get_ancestors(all_nodes);
        return std::move(ancestors);
    }

    std::string Node::to_dot() const
    {
        auto nodes = this->all_nodes();
        return Node::to_dot(nodes);
    }

    Node *Node::shallow_copy() const { return new Node(*this); }

    Node *Node::deep_copy() const
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
    Node *Node::shallow_copy(const Node *root) { return root ? new Node(*root) : nullptr; }
    Node *Node::deep_copy(const Node *root) { return root ? root->deep_copy() : nullptr; }

}
