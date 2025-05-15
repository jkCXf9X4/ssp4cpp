#pragma once

#include "FMI2_modelDescription.hpp"
#include "common_log.hpp"

#include <string>
#include <vector>
#include <filesystem>
#include <optional>
#include <format>

using namespace std;
using namespace std::filesystem;


namespace ssp4cpp
{

    class Fmu
    {
    public:
        path original_file;
        path temp_dir;
        fmi2::md::fmi2ModelDescription md;
        common::Logger log;

        Fmu(const path &file);

        ~Fmu();

        friend ostream &operator<<(ostream &os, const Fmu &obj)
        {
            os << "Fmu { \n"
               << "original_file: " << obj.original_file << endl
               << "temp_dir: " << obj.temp_dir << endl
               << "md: " << obj.md.modelName << endl
               << " }" << endl;

            return os;
        }
        
        std::string to_str()
        {
            return common::str::stream_to_str(this);
        }

    private:
        static fmi2::md::fmi2ModelDescription parse_model_description(const string &fileName);
    };

}