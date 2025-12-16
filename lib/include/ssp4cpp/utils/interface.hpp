#pragma once

#include <string>
#include <ostream>

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

    /** @brief Interface for XML serializable nodes. */
    class IXmlNode : public IWritable
    {
    };

    class IPrintable
    {
    public:
        virtual ~IPrintable();

        std::string to_string() const;

        friend std::ostream &operator<<(std::ostream &os, const IPrintable &obj)
        {
            obj.print(os); // delegate to virtual function
            return os;
        }

        virtual void print(std::ostream &os) const
        {
            os << "IPrintable {}"; // default representation
        }
    };
}
