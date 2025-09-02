#pragma once

#include "FMI2_modelDescription.hpp"

#include "archive.hpp"

#include <string>
#include <vector>


namespace ssp4cpp
{

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
        Fmu(const std::filesystem::path &file);

        friend std::ostream &operator<<(std::ostream &os, const Fmu &obj)
        {
            os << "Fmu { \n"
               << "original_file: " << obj.original_file << std::endl
               << "dir: " << obj.dir << std::endl
               << "modelName: " << obj.md->modelName << std::endl
               << " }" << std::endl;

            return os;
        }

    };

}