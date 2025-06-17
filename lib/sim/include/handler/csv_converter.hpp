// convert_log_grouped.cpp
#pragma once

#include "common_log.hpp"
#include "common_time.hpp"

#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <map>
#include <vector>

namespace ssp4cpp::sim
{

    void convert_to_csv(std::string temp_file, std::string output_file)
    {
        auto log = common::Logger("convert_to_csv", common::LogLevel::debug);
        std::ifstream in(temp_file);
        if (!in)
        {
            log.error("Cannot open {}", temp_file);
            return;
        }

        log.trace("1. Build memory map");

        std::unordered_map<int, std::string> ref_to_name;
        std::map<long long, std::unordered_map<int, std::string>> rows; // time -> {ref -> data}

        std::string line;
        while (std::getline(in, line))
        {
            if (line.empty())
                continue;

            std::stringstream ss(line);
            std::string first;
            std::getline(ss, first, ',');

            if (first == "REGISTER")
            {
                // REGISTER,signal_name,ref"
                log.ext_trace("Process new registration");

                std::string full_name, ref_str;
                std::getline(ss, full_name, ',');
                std::getline(ss, ref_str, ',');
                ref_to_name[std::stoi(ref_str)] = full_name;
            }
            else
            {
                // time,ref,data
                log.ext_trace("New data row");

                const long long time = std::stoll(first);
                std::string ref_str, data;
                std::getline(ss, ref_str, ',');
                std::getline(ss, data, ',');

                const int ref = std::stoi(ref_str);
                rows[time][ref] = data;
            }
        }
        in.close();

        log.trace("2. Prepare ordered list of references for header");
        std::vector<int> ordered_refs;
        ordered_refs.reserve(ref_to_name.size());
        for (const auto &p : ref_to_name)
        {
            ordered_refs.push_back(p.first);
        }
        std::sort(ordered_refs.begin(), ordered_refs.end());

        log.trace("3. Write CSV");
        std::ofstream out(output_file);
        if (!out)
        {
            log.error("Cannot create {}", output_file);
            return;
        }

        log.ext_trace("Print header");
        out << "time";
        for (int ref : ordered_refs)
            out << ',' << ref_to_name[ref];
        out << '\n';

        log.ext_trace("Write data rows");
        for (const auto &[time, refmap] : rows)
        {
            double time_double = (double)time / common::time::nanoseconds_per_second;
            out << time_double;
            for (int ref : ordered_refs)
            {
                out << ',';
                auto it = refmap.find(ref);
                if (it != refmap.end())
                    out << it->second; // value present
                // else leave empty cell
            }
            out << '\n';
        }
        out.close();
    }

}