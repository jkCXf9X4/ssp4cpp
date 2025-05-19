
#pragma once

#include "common_node.hpp"

#include <vector>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <algorithm> // std::min
#include <cassert>
#include <string>
#include <sstream>

namespace ssp4cpp::common::graph
{
    /******************************************************************
     *  Tarjan’s strongly–connected–components for Node (header-only)  *
     ******************************************************************/
    // Graciously implemented by chatGPT o3

    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*
    |  INTERNAL HELPER – keeps all state in one object so the public  |
    |  function is simple to call and the algorithm can recurse.      |
    *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    struct _TarjanSccImpl
    {
        // Per-node bookkeeping
        std::unordered_map<Node *, int> index;   // discovery index
        std::unordered_map<Node *, int> lowlink; // lowest reachable index
        std::unordered_set<Node *> onStack;      // membership test
        std::stack<Node *> S;                    // DFS stack

        int nextIndex = 0;                       // global DFS counter
        std::vector<std::vector<Node *>> result; // final SCCs

        void strongConnect(Node *v)
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
    };

    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*
    |  PUBLIC API – linear-time SCC detection on a set of nodes.      |
    |  Supply every node in your graph once (order does not matter).  |
    *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    inline std::vector<std::vector<Node *>> strongly_connected_components(
        const std::vector<Node *> &nodes)
    {
        _TarjanSccImpl impl;

        for (Node *v : nodes)
            if (impl.index.find(v) == impl.index.end())
                impl.strongConnect(v);

        return impl.result; // O(V + E)
    }

    inline std::string ssc_to_string(std::vector<std::vector<Node *>> ssc)
    {
        std::stringstream ss;
        ss << "Tarjans SSC Result" << std::endl;
        for (auto &strong : ssc)
        {
            ss << "Strongly connected group:" << std::endl;
            for (auto &node : strong)
            {
                ss << " - " << node->name << std::endl;
            }
        }
        return ss.str();
    }

}