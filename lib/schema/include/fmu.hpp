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

    /**
     * @brief Represents an FMU archive and its parsed model description.
     */
    class Fmu : public Archive
    {
    public:
        fmi2::md::fmi2ModelDescription md;

        /**
         * @brief Construct an FMU from a file path.
         */
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

        /** @brief Convert to string for debugging purposes. */
        std::string to_string()
        {
            return common::str::stream_to_str(*this);
        }

    private:
        /** @brief Parse the modelDescription.xml inside the FMU. */
        static fmi2::md::fmi2ModelDescription parse_model_description(const string &fileName);
    };

}