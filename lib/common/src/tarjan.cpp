
#include "tarjan.hpp"

namespace ssp4cpp::common::graph
{
    void _TarjanSccImpl::strongConnect(Node *v)
    {
        index[v] = nextIndex;
        lowlink[v] = nextIndex;
        ++nextIndex;

        S.push(v);
        onStack.insert(v);

        /* ---- DFS over all outgoing arcs ---- */
        for (Node *w : v->children)
        {
            if (index.find(w) == index.end()) // (1) tree-edge
            {
                strongConnect(w);
                lowlink[v] = std::min(lowlink[v], lowlink[w]);
            }
            else if (onStack.count(w)) // (2) back-edge
            {
                lowlink[v] = std::min(lowlink[v], index[w]);
            }
        }

        /* ---- root of an SCC? ---- */
        if (lowlink[v] == index[v])
        {
            std::vector<Node *> component;
            Node *w;
            do
            {
                w = S.top();
                S.pop();
                onStack.erase(w);
                component.push_back(w);
            } while (w != v);

            result.push_back(std::move(component));
        }
    }

    std::vector<std::vector<Node *>> strongly_connected_components(
        const std::vector<Node *> &nodes)
    {
        _TarjanSccImpl impl;

        for (Node *v : nodes)
            if (impl.index.find(v) == impl.index.end())
                impl.strongConnect(v);

        return impl.result; // O(V + E)
    }

    std::string ssc_to_string(std::vector<std::vector<Node *>> ssc)
    {
        std::stringstream ss;
        ss << "Tarjans SSC Result\n";
        for (auto &strong : ssc)
        {
            ss << "Strongly connected group:\n";
            for (auto &node : strong)
            {
                ss << " - " << node->name << "\n";
            }
        }
        return ss.str();
    }

}