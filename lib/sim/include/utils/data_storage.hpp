#pragma once

#include "common_node.hpp"
#include "common_map.hpp"
#include "common_string.hpp"
#include "common_time.hpp"

#include "FMI2_Enums_Ext.hpp"

#include "data_type.hpp"

#include <string>
#include <vector>
#include <map>
#include <memory>
#include <cstddef>

namespace ssp4cpp::sim::utils
{
    /*
     * data centric storage
     * the data storage area should enable:
     * - easy access when exporting results
     * - altering data in and out from the model
     * - store multiple time versions of the data to enable access backwards in time
     */

    class DataStorage : public common::str::IString
    {
    public:
        common::Logger log = common::Logger("DataStorage", common::LogLevel::debug);

        // all data
        std::unique_ptr<std::byte[]> data;
        std::unique_ptr<std::byte[]> der_data;

        // these are the same for each timestamp area
        std::vector<std::size_t> positions; // data position relative to start; 0, 4,...
        std::vector<size_t> der_positions;  // data position relative to start; 0, 4,...

        std::vector<utils::DataType> types;
        std::vector<std::string> names;
        std::vector<size_t> sizes;
        std::vector<size_t> max_interpolation_orders;

        // for retrieval of index from name
        std::map<std::string, std::size_t> index_name_map;

        std::vector<std::uint64_t> timestamps;
        std::vector<std::vector<std::byte *>> locations;     // absolute location in memory
        std::vector<std::vector<std::byte *>> der_locations; // absolute location in memory
        std::vector<bool> new_data_flags;

        std::size_t areas = 1;
        std::size_t pos = 0;
        std::size_t der_pos = 0;
        std::size_t total_size = 0;
        std::int32_t index = -1;
        std::size_t items = 0;
        std::string name;
        size_t derivative_size = sizeof(double);

        bool allocated = false;

        DataStorage(int areas)
        {
            this->areas = areas;
        }

        DataStorage(int areas, std::string name)
        {
            this->areas = areas;
            this->name = name;
        }

        uint32_t add(std::string name, utils::DataType type, int max_interpolation_order)
        {
            index += 1;
            items += 1;
            auto size = fmi2::ext::enums::get_data_type_size(type);
            index_name_map[name] = index;

            names.push_back(name);
            types.push_back(type);
            sizes.push_back(size);
            max_interpolation_orders.push_back(max_interpolation_order);

            positions.push_back(pos);
            this->der_positions.push_back(der_pos);

            pos += size;
            der_pos += max_interpolation_order * derivative_size;

            return index;
        }

        void allocate()
        {
            locations.clear();
            der_locations.clear();

            total_size = pos * areas;
            data = std::make_unique<std::byte[]>(total_size);
            std::memset(data.get(), 0, total_size);

            auto der_size = der_pos * areas;
            der_data = std::make_unique<std::byte[]>(der_size);
            std::memset(der_data.get(), 0, der_size);

            timestamps.resize(areas);
            locations.resize(areas);
            der_locations.resize(areas);

            for (int area = 0; area < areas; area++)
            {
                locations[area].reserve(positions.size());
                der_locations[area].reserve(der_positions.size());

                for (auto p_pos : positions)
                {
                    locations[area].push_back(&data[area * pos + p_pos]);
                }

                for (int i = 0; i < der_positions.size(); ++i)
                {
                    if (max_interpolation_orders[i] > 0)
                    {
                        der_locations[area].push_back(&der_data[area * der_pos + der_positions[i]]);
                    }
                    else
                    {
                        der_locations[area].push_back(nullptr);
                    }
                    
                }
                new_data_flags.push_back(false);

                // Initialize all strings with an empty string
                for (int index = 0; index < types.size(); index++)
                {
                    if (types[index] == utils::DataType::string)
                    {
                        log.debug("[{}] Setting string {}:{} - {}", __func__, index, names[index], types[index].to_string());
                        auto s = (std::string*)locations[area][index];
                        *s = std::string("");
                    }
                }
            }

            allocated = true;
        }

        inline std::byte *get_item(std::size_t area, std::size_t index) noexcept
        {
            if (allocated) [[likely]]
            {
                return locations[area][index];
            }
            return nullptr;
        }

        inline std::byte *get_derivative(std::size_t area, std::size_t index, std::size_t order) noexcept
        {
            if (allocated) [[likely]]
            {
                return der_locations[area][index] + (order - 1) * derivative_size;
            }
            return nullptr;
        }

        inline void set_time(std::size_t area, uint64_t time) noexcept
        {
            if (allocated) [[likely]]
            {
                timestamps[area] = time;
            }
        }

        inline void flag_new_data(std::size_t area)
        {
            if (allocated) [[likely]]
            {
                new_data_flags[area] = true;
            }
        }

        int index_by_name(std::string name)
        {
            return index_name_map[name];
        }

        virtual void print(std::ostream &os) const
        {
            os << "DataStorage \n{\n"
               << " name: " << name
               << "  areas: " << areas
               << ", allocated: " << allocated
               << ", total_size: " << total_size
               << ", pos: " << pos
               << ", items: " << items
               << ", index: " << index << "\n";

            for (int i = 0; i < items; i++)
            {
                os << "  { position " << positions[i]
                   << ", name " << names[i]
                   << ", type " << types[i]
                   << ", size " << sizes[i] << " }\n";
            }
            os << "}";
        }

        std::string export_area(int area)
        {
            std::ostringstream oss;
            oss << "\nArea: \n"
                << area;
            for (int i = 0; i < items; i++)
            {
                auto item = get_item(area, i);
                auto data_type_str = fmi2::ext::enums::data_type_to_string(types[i], item);
                oss << "{ position " << positions[i]
                    << ", der_position " << der_positions[i]
                    << ", der_orders " << max_interpolation_orders[i]
                    << ", der_loc " << (uint64_t)der_locations[area][i]
                    << ", name: " << names[i]
                    << ", type: " << types[i]
                    << ", size: " << sizes[i]
                    << ", value:" << data_type_str
                    << " }\n";
            }
            return oss.str();
        }
    };
}