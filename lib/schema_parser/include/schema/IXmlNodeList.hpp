#pragma once

#include "IXmlNode.hpp"
#include "to_string.hpp"

#include <string>
#include <vector>
#include <optional>
#include <stdexcept>
#include <sstream>

#include <type_traits>

namespace ssp4cpp::interfaces
{
    using namespace ssp4cpp::str;

    template <typename T>
    class IList : public IReadWrite
    {
    public:
        virtual std::string to_string() const
        {
            return ssp4cpp::str::to_str(list);
        }

        virtual void from_string(const std::string &str, const char del)
        {
            list.clear();

            std::istringstream ss;
            ss.str(str);
            for (std::string word; std::getline(ss, word, del);)
            {
                T item;

                if constexpr (std::is_same_v<T, int>)
                {
                    item = std::stoi(word);
                }
                else if constexpr (std::is_same_v<T, unsigned int>)
                {
                    item = std::stoul(word);
                }
                else if constexpr (std::is_same_v<T, double>)
                {
                    item = std::stod(word);
                }
                else if constexpr (std::is_same_v<T, bool>)
                {
                    item = word == "true";
                }
                else if constexpr (std::is_same_v<T, std::string>)
                {
                    item = word;
                }
                else if constexpr (std::is_base_of_v<IReadable, T>)
                {
                    item.from_string(word);
                }
                else
                {
                    throw std::runtime_error("Unsupported type");
                }

                list.push_back(item);
            }
        }

        // easy to overwrite
        virtual void from_string(const std::string &str)
        {
            from_string(str, ' ');
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
