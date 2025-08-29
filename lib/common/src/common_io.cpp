#include "common_io.hpp"

#include <string>
#include <fstream>

namespace ssp4cpp::common::io
{
    void save_string(const std::string &filename, const std::string &content)
    {
        std::ofstream myfile;
        myfile.open(filename);
        myfile << content;
        myfile.close();
    }
}