
#include "dsm.hpp"

#include <vector>
#include <iostream>
#include <numeric>
#include <ranges>
#include <format>

namespace ssp4cpp::dsm
{
    DSM::DSM(Graph &g) : g_ref(g)
    {
        N = num_vertices(g);
        matrix = Matrix<int>(N);
 
        // group_order
        std::map<std::string, int> comp_map;
        int group_id = 1;
        graph_traits<Graph>::edge_iterator ei, ei_end;
        for (tie(ei, ei_end) = edges(g); ei != ei_end; ++ei)
        {
            int row = source(*ei, g); // Source vertex of the edge
            int column = target(*ei, g); // Target vertex of the edge
            matrix[row, column] = 1;      // Mark the edge in the DSM

            auto component = g[row].component;
            if(!comp_map.contains(component))
            {
                std::cout << component << " : " << group_id << std::endl;
                comp_map[component] = group_id++;
            }
            matrix.set_group(row, comp_map[component]);

        }


    }

    void DSM::PrintGroups()
    {
        std::string out = "";
        auto groups = matrix.get_group_map();
        for (int i = 0; i < N; i++)
        {
            out += std::format("Row: {} group: {}\n", i,  groups[i]);
        }
        std::cout << out;
    }


    std::string DSM::GetCSV()
    {
        std::string out = "";
        for (int i = 0; i < N; i++)
        {
            if (i == 0)
            {
                out += "node";
                for (int j = 0; j < N; j++)
                {
                    // if (matrix.column_has_value(j))
                    {
                        out += std::format(";{}", g_ref[j].name);
                    }
                }
                out += "\n";
            }
            // if (matrix.row_has_value(i))
            {
                out += g_ref[i].name;
                for (int j = 0; j < N; j++)
                {
                    // if (matrix.column_has_value(j))
                    {
                        out += std::format(";{}", matrix[i, j]);
                    }
                }
                out += "\n";
            }
        }
        return out;
    }

}