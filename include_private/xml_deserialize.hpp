// #pragma once

#include <pugixml.hpp>

#include <optional>
#include <stdexcept>
#include <string>
#include <iostream>
#include <vector>

#include "IXmlNode.hpp"

// deserialize xml to object

namespace ssp4cpp::xml
{
    namespace
    {
        template <typename>
        constexpr bool is_optional_impl = false;
        template <typename T>
        constexpr bool is_optional_impl<std::optional<T>> = true;
        template <>
        constexpr bool is_optional_impl<std::nullopt_t> = true;

        template <typename T>
        constexpr bool is_optional_v = is_optional_impl<std::decay_t<T>>;

        template <typename C>
        struct is_vector : std::false_type
        {
        };
        template <typename T, typename A>
        struct is_vector<std::vector<T, A>> : std::true_type
        {
        };
        template <typename C>
        inline constexpr bool is_vector_v = is_vector<C>::value;

    }

    using namespace std;
    using namespace pugi;

    template <typename T>
    void get_attribute(const xml_node &node, T &obj, const string &name)
    {
        // cout << "get_attribute: " << name << endl;
        if constexpr (is_same_v<T, int>)
        {
            obj = node.attribute(name.c_str()).as_int();
        }
        else if constexpr (is_same_v<T, unsigned int>)
        {
            obj = node.attribute(name.c_str()).as_uint();
        }
        else if constexpr (is_same_v<T, double>)
        {
            obj = node.attribute(name.c_str()).as_double();
        }
        else if constexpr (is_same_v<T, bool>)
        {
            obj = node.attribute(name.c_str()).as_bool();
        }
        else if constexpr (is_same_v<T, string>)
        {
            obj = node.attribute(name.c_str()).as_string();
        }
        else
        {
            throw runtime_error("Unable to parse attribute: " + name + " : " + typeid(T).name());
        }
    }

    template <typename T>
    void get_class(const xml_node &node, T &obj, const string &name)
    {
        // cout << "get_class: " << name << endl;
        obj = T();
        auto child = node.child(name.c_str());
        from_xml(child, obj);
    }

    template <typename T>
    void get_vector(const xml_node &node, vector<T> &list, const string &name)
    {
        // cout << "get_vector: " << name + " : " + typeid(T).name() << endl;
        for (auto child : node.children(name.c_str()))
        {
            T t;
            from_xml(child, t);
            list.push_back(t);
        }
    }

    template <typename T>
    void get_optional_attribute(const xml_node &node, optional<T> &obj, const string &name)
    {
        // cout << "get_optional_attribute: " << name << endl;
        if (node.attribute(name.c_str()).empty())
        {
            obj = nullopt;
        }
        else
        {
            obj = T();
            get_attribute(node, *obj, name);
        }
    }

    template <typename T>
    void get_optional_class(const xml_node &node, optional<T> &obj, const string &name)
    {
        // cout << "get_optional_class: " << name << endl;
        if (node.child(name.c_str()))
        {
            obj = T();
            get_class(node, *obj, name);
        }
        else
        {
            obj = nullopt;
        }
    }

    template <typename T, typename = std::enable_if<!is_vector_v<T> && !is_optional_v<T>>>
    void parse_xml(const xml_node &node, T &obj, const string &name)
    {
        // cout << "parse_xml: " << name << endl;
        if constexpr (is_same_v<T, int> ||
                      is_same_v<T, unsigned int> ||
                      is_same_v<T, double> ||
                      is_same_v<T, bool> ||
                      is_same_v<T, string>)
        {
            get_attribute(node, obj, name);
        }
        else if constexpr (is_base_of_v<IXmlNode, T>) // class
        {
            get_class(node, obj, name);
        }
        else if constexpr (is_base_of_v<IXmlNodeEnum, T>)
        {
            auto s = node.attribute(name.c_str()).as_string();
            obj.from_string(s);
        }
        else
        {
            throw runtime_error("Unreachable parse_xml_norm: " + name + " : " + typeid(T).name());
        }
    }

    template <typename T, typename = std::enable_if<is_optional_v<T>>>
    void parse_xml(const xml_node &node, optional<T> &obj, const string &name)
    {
        // cout << "parse_xml <optional>: " << name << endl;
        if constexpr (is_same_v<T, int> ||
                      is_same_v<T, unsigned int> ||
                      is_same_v<T, double> ||
                      is_same_v<T, bool> ||
                      is_same_v<T, string>)
        {
            get_optional_attribute(node, obj, name);
        }
        else if constexpr (is_base_of_v<IXmlNode, T>)
        {
            get_optional_class(node, obj, name);
        }
        else if constexpr (is_base_of_v<IXmlNodeEnum, T>)
        {
            throw runtime_error("Not implemented... : " + name + " : " + typeid(T).name());
        }
        else
        {
            throw runtime_error("Unreachable : " + name + " : " + typeid(T).name());
        }
    }

    template <typename T, typename = std::enable_if<is_vector_v<T>>>
    void parse_xml(const xml_node &node, vector<T> &obj, const string &name)
    {
        // cout << "parse_xml <vector>: " + name + " : " + typeid(T).name() << endl;
        if constexpr (is_base_of_v<IXmlNode, T>)
        {
            get_vector(node, obj, name);
        }
        else if constexpr (is_base_of_v<IXmlNodeEnum, T>)
        {
            throw runtime_error("Not implemented... : " + name + " : " + typeid(T).name());
        }
        else
        {
            throw runtime_error("Unreachable : " + name + " : " + typeid(T).name());
        }
    }

}