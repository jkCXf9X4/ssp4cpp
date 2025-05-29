
#pragma once

#include <string>
#include <fstream>


namespace ssp4cpp::common::io
{

    void save_string(const std::string &filename, const std::string &content)
    {
        ofstream myfile;
        myfile.open(filename);
        myfile << content;
        myfile.close();
    }
    
    
}