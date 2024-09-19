#pragma once

#include <string>

class IXmlNode
{
    public:
        virtual std::string to_string() const = 0;
};