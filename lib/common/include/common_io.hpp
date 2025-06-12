
#pragma once

#include <string>
#include <fstream>


namespace ssp4cpp::common::io
{

    /**
     * @brief Write a string to a file, overwriting any existing content.
     */
    void save_string(const std::string &filename, const std::string &content)
    {
        ofstream myfile;
        myfile.open(filename);
        myfile << content;
        myfile.close();
    }
    
    
}