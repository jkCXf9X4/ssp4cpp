
#include "dsm.hpp"

#include <vector>
#include <iostream>
#include <numeric>
#include <ranges>

namespace ssp4cpp::dsm
{
    DSM::DSM(Graph g)
    {
        N = num_vertices(g);
        dsm_row = std::vector(N, std::vector<int>(N, 0));
        dsm_column = std::vector(N, std::vector<int>(N, 0));

        graph_traits<Graph>::edge_iterator ei, ei_end;
        for (tie(ei, ei_end) = edges(g); ei != ei_end; ++ei)
        {
            int u = source(*ei, g); // Source vertex of the edge
            int v = target(*ei, g); // Target vertex of the edge
            dsm_row[u][v] = 1;      // Mark the edge in the DSM
            dsm_column[v][u] = 1;   // Mark the edge in the DSM
        }
    }

    void DSM::Print(std::map<int, std::string> name_map)
    {
        auto print_row = std::vector<int>(N);
        auto print_column = std::vector<int>(N);

        for (int i = 0; i < N; i++)
        {
            print_row[i] = std::accumulate(dsm_row[i].begin(), dsm_row[i].end(), 0) != 0;
            print_column[i] = std::accumulate(dsm_column[i].begin(), dsm_column[i].end(), 0) != 0;
            // std::cout << print_row[i] << std::endl;
        }

        // Display the DSM matrix
        std::cout << "Design Structure Matrix (DSM):" << std::endl;
        for (int i = 0; i < N; i++)
        {
            if (i == 0)
            {
                for (int j = 0; j < N; j++)
                {
                    if (print_column[j])
                    {
                        std::cout << ";" << name_map[j];
                    }
                }
                std::cout << std::endl;
            }
            if (print_row[i])
            {
                std::cout << name_map[i];
                for (int j = 0; j < N; j++)
                {
                    if (print_column[j])
                    {

                        std::cout << ";" << dsm_row[i][j];
                    }
                }

                std::cout << std::endl;
            }
        }
    }

}