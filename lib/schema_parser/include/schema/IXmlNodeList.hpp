#pragma once

#include "IXmlNode.hpp"
#include "string_conversion.hpp"



namespace ssp4cpp::interfaces
{

    template <typename T>
    class IList : public IReadWrite
    {
    public:

        // Do not break these functions to a separate declaration
        // They are needed to provide the full declaration within the header

        virtual std::string to_string() const
        {
            return ssp4cpp::str::to_str<T>(list);
        }

        virtual void from_string(const std::string &str, const char del)
        {
            list = ssp4cpp::str::from_strs<T>(str, del);
        }

        virtual void from_string(const std::string &str)
        {
            list = ssp4cpp::str::from_strs<T>(str);
        }

        std::vector<T> list;
    };

    // some primitive variants to be used

    class IntList : public IList<int>
    {
    };

    class UIntList : public IList<unsigned int>
    {
    };

    class DoubleList : public IList<double>
    {
    };

    class BoolList : public IList<bool>
    {
    };

    class StringList : public IList<std::string>
    {
    };

} 
