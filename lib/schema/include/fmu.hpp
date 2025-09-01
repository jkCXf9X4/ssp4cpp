#pragma once

#include "FMI2_modelDescription.hpp"

#include "archive.hpp"

#include <string>
#include <vector>

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
        std::unique_ptr<fmi2::md::fmi2ModelDescription> md;

        /**
         * @brief Construct an FMU from a file path.
         */
        Fmu(const path &file);

        friend ostream &operator<<(ostream &os, const Fmu &obj)
        {
            os << "Fmu { \n"
               << "original_file: " << obj.original_file << endl
               << "dir: " << obj.dir << endl
               << "modelName: " << obj.md->modelName << endl
               << " }" << endl;

            return os;
        }

        /** @brief Convert to string for debugging purposes. */
        std::string to_string();

    };

}