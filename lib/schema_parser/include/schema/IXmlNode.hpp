#pragma once

#include <string>

namespace ssp4cpp::interfaces
{

    class IWritable
    {
    public:
        virtual std::string to_string() const = 0;
    };

    class IReadable
    {
    public:
        virtual void from_string(const std::string &str) = 0;
    };

    class IReadWrite : public IWritable, public IReadable
    {
    };

    class IXmlNode : public IWritable
    {
    };

    class IEnum : public IReadWrite
    {
    };
}
