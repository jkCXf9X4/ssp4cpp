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


namespace ssp4cpp::fmi2
{

    class FmiImport
    {
    public:
        path original_file;
        path temp_dir;
        md::fmi2ModelDescription md;
        common::Logger log;

        FmiImport(const path &file);

        ~FmiImport();

        friend ostream &operator<<(ostream &os, const FmiImport &obj)
        {
            os << "FmiImport { \n"
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
        static md::fmi2ModelDescription parse_model_description(const string &fileName);
    };

}