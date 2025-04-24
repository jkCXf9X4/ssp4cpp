#pragma once

#include "common_interface.hpp"
#include "common_string.hpp"

namespace ssp4cpp::schema
{
    using namespace ssp4cpp::common::str;

    template <typename T>
    class NodeList : public ssp4cpp::common::interfaces::IList
    {
    public:

        std::string to_string() const
        {
            return to_str<T>(list);
        }

        void from_string(const std::string &str, const char del)
        {
            list = from_strs<T>(str, del);
        }

        void from_string(const std::string &str)
        {
            list = from_strs<T>(str);
        }
        std::vector<T> list;
    };

    // some primitive variants to be used

    class IntList : public NodeList<int>
    {
    };

    class UIntList : public NodeList<unsigned int>
    {
    };

    class DoubleList : public NodeList<double>
    {
    };

    class BoolList : public NodeList<bool>
    {
    };

    class StringList : public NodeList<std::string>
    {
    };

} 
