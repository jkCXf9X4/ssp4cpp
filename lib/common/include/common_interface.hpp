#pragma once

#include <string>

namespace ssp4cpp::common::interfaces
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

    class IEnum : public IReadWrite
    {
    };

    class IList : public IReadWrite
    {
        virtual void from_string(const std::string &str, const char del) = 0;
    };

    class IXmlNode : public IWritable
    {
    };

    class IXmlNodeList : public IList
    {
    };
}
