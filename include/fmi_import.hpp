#pragma once

#include "modelDescription.hpp"

#include <string>
#include <vector>
#include <filesystem>
#include <optional>


using namespace std;
using namespace std::filesystem;

namespace ssp4cpp::fmi2
{

    class FmiImport
    {
    public:
        path original_file;
        path temp_dir;
        fmi2ModelDescription md;

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

    private:
        fmi2ModelDescription parse_model_description(const string &fileName);
    };

}