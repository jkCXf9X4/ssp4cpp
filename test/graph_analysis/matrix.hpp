#pragma once

#include "misc.hpp"

#include <vector>
#include <map>
#include <stdexcept>
#include <numeric>

namespace ssp4cpp::dsm
{
    template <typename T>
    class Matrix
    {
    public:
        Matrix(size_t size = 0) : N(size)
        {
            matrix = std::vector<std::vector<T>>(size, std::vector<T>(size, T()));
        }

        int& operator[](int row, int column)
        {
            return matrix[row][column];
        }

        void set_group(int row, int group)
        {
            group_map[row] = group;
        }

        std::vector<int> get_groups()
        {
            auto groups = std::vector<int>();

            for (auto [key, group]: group_map)
            {
                if (misc::is_in_list(group, groups))
                {
                    groups.push_back(group);
                }
            }
            return groups;
        }


        // Function to get a reference to a specific row
        std::vector<T> row(size_t index)
        {
            if (index < 0 || index >= N)
            {
                throw std::out_of_range("Row index out of range");
            }
            std::vector<T> row(N);
            for (size_t i = 0; i < N; ++i)
            {
                row[i] = matrix[index][i];
            }
            return row;
        }

        // Function to get a specific column as a vector
        std::vector<T> column(size_t index) const
        {
            if (index < 0 || index >= N)
            {
                throw std::out_of_range("Column index out of range");
            }
            std::vector<T> column(N);
            for (size_t i = 0; i < N; ++i)
            {
                column[i] = matrix[i][index];
            }
            return column;
        }

        Matrix<T> Transpose()
        {
            Matrix<T> mat(N);
            for (int i = 0; i < N; i++)
            {
                for (int j = 0; j < N; j++)
                {
                    mat[i][j] = matrix[j][i];
                }
            }
            return mat;
        }

        T row_sum(size_t index)
        {
            auto row = this->row(index);
            return std::accumulate(row.begin(), row.end(), 0);
        }

        T column_sum(size_t index)
        {
            auto column = this->column(index);
            return std::accumulate(column.begin(), column.end(), 0);
        }

        bool row_has_value(size_t index)
        {
            return row_sum(index) != 0;
        }

        bool column_has_value(size_t index)
        {
            return row_sum(index) != 0;
        }

    private:
        size_t N;
        std::vector<std::vector<T>> matrix;
        std::map<int, int> group_map = {};
    };
}
