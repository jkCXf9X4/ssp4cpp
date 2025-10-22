#pragma once

#include "ssp4cpp/utils/archive.hpp"
#include "ssp4cpp/schema/fmi2/FMI2_modelDescription.hpp"

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
            os << "Fmu {"
               << "\noriginal_file: " << original_file
               << "\ndir: " << dir
               << "\nmodelName: " << md->modelName
               << "\n}\n";
        }

    };

}
