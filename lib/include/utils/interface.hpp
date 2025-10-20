#pragma once

#include <string>

namespace ssp4cpp::utils::interfaces
{

    /** @brief Interface for objects that can be converted to string. */
    class IWritable
    {
    public:
        virtual std::string to_string() const = 0;
    };

    /** @brief Interface for objects that can be created from a string. */
    class IReadable
    {
    public:
        virtual void from_string(const std::string &str) = 0;
    };

    /** @brief Convenience interface combining IWritable and IReadable. */
    class IReadWrite : public IWritable, public IReadable
    {
    };

    /** @brief Marker interface for enum like types. */
    class IEnum : public IReadWrite
    {
    };

    /** @brief Interface for list types that can be serialized/deserialized. */
    class IList : public IReadWrite
    {
        virtual void from_string(const std::string &str, const char del) = 0;
    };

    /** @brief Interface for XML serializable nodes. */
    class IXmlNode : public IWritable
    {
    };

    /** @brief Interface for lists of XML nodes. */
    class IXmlNodeList : public IList
    {
    };
}
