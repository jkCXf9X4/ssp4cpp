#pragma once

#include "archive.hpp"
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

    class Fmu : public Archive
    {
    public:
        fmi2::md::fmi2ModelDescription md;

        Fmu(const path &file) : Archive(file, "fmi_")
        {
            log = Logger("Fmu", LogLevel::debug);
            md = parse_model_description((dir / "modelDescription.xml").string());
        }

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