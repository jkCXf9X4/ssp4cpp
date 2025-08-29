
#pragma once

#include "common_node.hpp"

#include <vector>
#include <stack>
#include <unordered_map>
#include <unordered_set>

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

        void strongConnect(Node *v);
    };

    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*
    |  PUBLIC API – linear-time SCC detection on a set of nodes.      |
    |  Supply every node in your graph once (order does not matter).  |
    *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /**
     * @brief Compute strongly connected components using Tarjan's algorithm.
     *
     * @param nodes Vector containing each node in the graph exactly once.
     * @return List of components, each component being a vector of nodes.
     */
    std::vector<std::vector<Node *>> strongly_connected_components(
        const std::vector<Node *> &nodes);

    /**
     * @brief Utility to pretty print the list of components returned by
     *        strongly_connected_components().
     */
    std::string ssc_to_string(std::vector<std::vector<Node *>> ssc);

}