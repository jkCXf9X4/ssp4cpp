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
    using namespace std;
    using namespace pugi;

    template <typename T>
    T get_attribute(const xml_node &node, const string &name)
    {
        auto attrib = node.attribute(name.c_str());
        if constexpr (is_same_v<T, int>)
        {
            return attrib.as_int();
        }
        else if constexpr (is_same_v<T, unsigned int>)
        {
            return attrib.as_uint();
        }
        else if constexpr (is_same_v<T, double>)
        {
            return attrib.as_double();
        }
        else if constexpr (is_same_v<T, bool>)
        {
            return attrib.as_bool();
        }
        else if constexpr (is_same_v<T, string>)
        {
            return attrib.as_string();
        }
        else
        {
            throw runtime_error("Unable to parse attribute: " + name);
        }
    }

    template <typename T>
    void get_attribute_2(const xml_node &node, T obj, const string &name)
    {
        auto attrib = node.attribute(name.c_str());
        if constexpr (is_same_v<T, int>)
        {
            obj = attrib.as_int();
        }
        else if constexpr (is_same_v<T, unsigned int>)
        {
            obj =  attrib.as_uint();
        }
        else if constexpr (is_same_v<T, double>)
        {
            obj =  attrib.as_double();
        }
        else if constexpr (is_same_v<T, bool>)
        {
            obj =  attrib.as_bool();
        }
        else if constexpr (is_same_v<T, string>)
        {
            obj =  attrib.as_string();
        }
        else
        {
            throw runtime_error("Unable to parse attribute: " + name);
        }
    }

    template <typename T>
    optional<T> get_optional_attribute(const xml_node &node, const string &name)
    {
        if (node.attribute(name.c_str()).empty())
        {
            return nullopt;
        }
        return get_attribute<T>(node, name);
    }

    template <typename T>
    void get_optional_attribute_2(const xml_node &node, optional<T> obj, const string &name)
    {
        if (node.attribute(name.c_str()).empty())
        {
            obj = nullopt;
        }
        get_attribute_2(node, obj, name);
    }

    template <typename T>
    void get_optional_class(const xml_node &node, const char *name, optional<T> &obj)
    {
        if (auto child = node.child(name))
        {
            obj = T(); // check!
            from_xml(child, *obj);
        }
    }

    template <typename T>
    void get_vector(const xml_node &node, const char *name, vector<T> &list)
    {
        for (auto child : node.children(name))
        {
            T t;
            from_xml(child, t);
            list.push_back(t);
        }
    }

    template <typename T>
    void parse_xml(const xml_node &node, T &obj, const string &name)
    {
        if constexpr (is_same_v<T, int> ||
                           is_same_v<T, unsigned int> ||
                           is_same_v<T, double> ||
                           is_same_v<T, bool> ||
                           is_same_v<T, string>)
        {
            get_attribute_2(node, obj, name);
        }
        else if constexpr (is_same_v<T, optional<int>> ||
                           is_same_v<T, optional<unsigned int>> ||
                           is_same_v<T, optional<double>> ||
                           is_same_v<T, optional<bool>> ||
                           is_same_v<T, optional<string>>)
        {
            get_optional_attribute_2(node, obj, name);
        }
        else if constexpr (is_base_of_v<IXmlNode, T>) // class
        {
            from_xml(node.child(name.c_str()), obj);
        }
        else if constexpr (is_same_v<T, vector<T>>) // vector
        {
            get_vector(node, name, obj);
        }
        else if constexpr (is_same_v<T, optional<T>>) // optional
        {
            get_optional_class(node, name, obj);
        }
        else if constexpr (is_base_of_v<IXmlNodeEnum, T>)
        {
            auto s = node.attribute(name.c_str()).as_string();
            obj.from_string(s);
        }
        else
        {
            throw runtime_error("Unreachable : " + name);
        }
    }
}