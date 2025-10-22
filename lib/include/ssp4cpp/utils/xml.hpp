
#pragma once

#include "ssp4cpp/utils/interface.hpp"
#include "ssp4cpp/utils/string.hpp"

#include <vector>

namespace ssp4cpp::utils::xml
{
    /**
     * @brief Helper container implementing IXmlNodeList for simple types.
     */
    template <typename T>
    class XmlNodeList : public utils::interfaces::IXmlNodeList
    {
    public:
        std::string to_string() const
        {
            return utils::str::to_str<T>(list);
        }

        void from_string(const std::string &str, const char del)
        {
            list = utils::str::from_strs<T>(str, del);
        }

        void from_string(const std::string &str)
        {
            list = utils::str::from_strs<T>(str);
        }
        std::vector<T> list;
    };

    // some primitive variants to be used

    class IntXmlList : public XmlNodeList<int>
    {
    };

    class UIntXmlList : public XmlNodeList<unsigned int>
    {
    };

    class DoubleXmlList : public XmlNodeList<double>
    {
    };

    class BoolXmlList : public XmlNodeList<bool>
    {
    };

    class StringXmlList : public XmlNodeList<std::string>
    {
    };
}
