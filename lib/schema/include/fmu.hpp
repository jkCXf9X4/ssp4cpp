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

        virtual void print(std::ostream &os) const
        {
            os << "Fmu { \n"
               << "original_file: " << original_file << std::endl
               << "dir: " << dir << std::endl
               << "modelName: " << md->modelName << std::endl
               << " }" << std::endl;
        }

    };

}