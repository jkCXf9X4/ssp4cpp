#pragma once

#include <string>

namespace ssp4cpp::interfaces
{

    // Writable
    class IWritable
    {
    public:
        virtual std::string to_string() const = 0;
    };

    // Readable
    class IReadable
    {
    public:
        virtual void from_string(const std::string &str) = 0;
    };

    // Readable and Writable
    class IReadWrite : public IWritable, public IReadable
    {
    };

    // Node
    class IXmlNode : public IWritable
    {
    };

    // Enumeration
    class IEnum : public IReadWrite
    {
    };

}
