#pragma once

#include <string>

class IXmlNode
{
    public:
        virtual std::string to_string() const = 0;
};

class IXmlNodeEnum
{
    public:
        virtual std::string to_string() const = 0;
        virtual void from_string(const std::string &str) = 0;
};
