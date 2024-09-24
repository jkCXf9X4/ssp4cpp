#pragma once

#include <string>
#include <vector>
#include <optional>
#include <stdexcept>

#include <type_traits>

#include "IXmlNode.hpp"
#include "to_string.hpp"

namespace ssp4cpp::interfaces
{
    using namespace ssp4cpp::str;

    // it should support same interface as IXmlNodeEnum
    template <typename T>
    class IXmlNodeEnumList : IXmlNodeEnum
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
                else if constexpr (std::is_base_of_v<IXmlNodeEnum, T>)
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

    class IntList : public IXmlNodeEnumList<int>
    {
    };

    class UIntList : public IXmlNodeEnumList<unsigned int>
    {
    };

    class DoubleList : public IXmlNodeEnumList<double>
    {
    };

    class BoolList : public IXmlNodeEnumList<bool>
    {
    };

    class StringList : public IXmlNodeEnumList<std::string>
    {
    };

    // // it should support same interface as IXmlNodeEnum
    // template <typename T>
    // class IXmlNodePrimitiveList : IXmlNodeEnum
    // {
    // public:
    //     virtual std::string to_string() const
    //     {
    //         return to_str(list);
    //         // std::string str = "";
    //         // for (const auto &item : list)
    //         // {
    //         //     if constexpr (std::is_same_v<T, bool>)
    //         //     {
    //         //         str += item ? "true" : "false";
    //         //     }
    //         //     else if constexpr (std::is_same_v<T, std::string>)
    //         //     {
    //         //         str += item;
    //         //     }
    //         //     else
    //         //     {
    //         //         str += std::to_string(item);
    //         //     }
    //         //     {

    //         //         str += ", ";
    //         //     }
    //         //     return str;
    //         // }
    //     }
    //     virtual void from_string(const std::string &str, const char del)
    //     {
    //         list.clear();

    //         std::istringstream ss;
    //         ss.str(str);
    //         for (std::string word; std::getline(ss, word, del);)
    //         {
    //             T item;
    //             if constexpr (std::is_same_v<T, int>)
    //             {
    //                 item = std::stoi(word);
    //             }
    //             else if constexpr (std::is_same_v<T, unsigned int>)
    //             {
    //                 item = std::stoul(word);
    //             }
    //             else if constexpr (std::is_same_v<T, double>)
    //             {
    //                 item = std::stod(word);
    //             }
    //             else if constexpr (std::is_same_v<T, bool>)
    //             {
    //                 item = word == "true";
    //             }
    //             else
    //             {
    //                 throw std::runtime_error("Unsupported type");
    //             }
    //             list.push_back(item);
    //         }
    //     }

    //     // easy to overwrite
    //     virtual void from_string(const std::string &str)
    //     {
    //         from_string(str, ' ');
    //     }

    //     std::vector<T> list;
    // };

} // namespace ssp4cpp::str
