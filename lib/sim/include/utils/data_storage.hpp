#pragma once

#include "common_node.hpp"
#include "common_map.hpp"
#include "common_string.hpp"
#include "common_time.hpp"

#include "data_type.hpp"

#include <string>
#include <vector>
#include <map>
#include <memory>
#include <cstddef>

namespace ssp4cpp::sim::utils
{
    // data centric storage
    // the data landing area enables easy access when exporting results
    // store multiple time versions of the data

    class DataStorage
    {
    public:
        common::Logger log = common::Logger("DataStorage", common::LogLevel::ext_trace);

        // all data
        std::unique_ptr<std::byte[]> data;

        // these are the same for each timestamp area
        std::vector<std::size_t> positions; // data position relative to start; 0, 4,...
        std::vector<utils::DataType> types;
        std::vector<std::string> names;

        // for retrieval of index from name
        std::map<std::string, std::size_t> index_name_map;

        std::vector<std::uint64_t> timestamps;
        std::vector<std::vector<std::byte *>> locations; // absolute location in memory

        std::size_t pos = 0;
        std::size_t index = -1;
        std::size_t areas = 1;

        DataStorage() {}

        DataStorage(int areas)
        {
            this->areas = areas;
        }

        uint64_t add(std::string name, utils::DataType type)
        {
            index += 1;

            names.push_back(name);
            positions.push_back(pos);
            types.push_back(type);

            index_name_map[name] = index;

            pos += utils::get_data_type_size(type);

            return index;
        }

        void allocate()
        {
            locations.clear();
            data = std::make_unique<std::byte[]>(pos * areas);

            timestamps.resize(areas);
            locations.resize(areas);

            for (int i = 0; i < areas; i++)
            {
                locations[i].reserve(positions.size());

                for (auto p : positions)
                {
                    locations[i].push_back(&data[i * pos + p]);
                }
            }
        }

        inline std::byte *get_locaction(std::size_t area, std::size_t index) noexcept
        {
            return locations[area][index];
        }


        // int index_by_name(std::string name)
        // {
        //     return index_name_map[name];
        // }
    };
}