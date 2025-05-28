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

    using namespace common;

    class Fmu
    {
    public:
        Logger log = Logger("fmi2.Fmu", LogLevel::debug);
        bool using_tmp_dir = false;
        path original_file;
        path dir;
        fmi2::md::fmi2ModelDescription md;

        Fmu() {}
        Fmu(const path &file);

        ~Fmu();

        // Fmu &operator=(const Fmu &other);

        friend ostream &operator<<(ostream &os, const Fmu &obj)
        {
            os << "Fmu { \n"
               << "original_file: " << obj.original_file << endl
               << "dir: " << obj.dir << endl
               << "modelName: " << obj.md.modelName << endl
               << " }" << endl;

            return os;
        }

        std::string to_string()
        {
            return common::str::stream_to_str(*this);
        }

    private:
        static fmi2::md::fmi2ModelDescription parse_model_description(const string &fileName);
    };

}