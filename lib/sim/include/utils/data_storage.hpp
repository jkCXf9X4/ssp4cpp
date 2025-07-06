#pragma once

#include "common_node.hpp"
#include "common_map.hpp"
#include "common_string.hpp"
#include "common_time.hpp"

#include "data_type.hpp"

#include <string>
#include <vector>
#include <map>

namespace ssp4cpp::sim::utils
{
    // data centric storage
    // the data landing area enables easy access when exporting results
    // store multiple time versions of the data

    template <typename T>
    class DataStorage
    {
    public:
        common::Logger log = common::Logger("DataStorage", common::LogLevel::ext_trace);

        // all data
        unique_ptr<std::byte[]> data;

        // these are the same for each timestamp area
        vector<int> positions; // data position relative to start, 0, 4,...
        vector<DataType> types;
        vector<std::string> names;

        // for retrieval of index from name
        map<std::string, int> index_name_map;

        vector<uint64_t> timestamps;
        // located by <area id, variable index>
        vector<vector<void *>> locations; // absolute location in memory
        vector<pair<utils::DataType, void *>> type_data;

        int pos = 0;
        int index = 0;
        int areas = 1;

        DataStorage() {}

        DataStorage(int areas)
        {
            this->areas = areas;
        }

        uint64_t add(T &item)
        {
            names.push_back(item.name);
            positions.push_back(pos);
            types.push_back(item.type);

            index_name_map[item.name] = index;

            pos += utils::get_data_type_size(item.type);
            index += 1;

            return index - 1;
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

        // int index_by_name(std::string name)
        // {
        //     return index_name_map[name];
        // }
    };
}