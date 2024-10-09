#pragma once
#include "IXmlNode.hpp"

#include <pugixml.hpp>

#include <optional>
#include <stdexcept>
#include <string>
#include <iostream>
#include <vector>


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
    using namespace ssp4cpp::interfaces;

    inline string parents_to_string(const xml_node &node)
    {
        string s = string(node.name());
        for (auto p = node.parent(); p; p = p.parent())
        {
            s = string(p.name()) + "/" + s;
        }
        return s;
    }

    template <typename T>
    void get_attribute(const xml_node &node, T &obj, const string &name)
    {
        auto attr = node.attribute(name.c_str());
        if (attr.empty())
        {
            string erro_msg = "ERROR: In Node: " + parents_to_string(node) + "\n Attribute not found: " + name;
            throw runtime_error(erro_msg);
        }

        if constexpr (is_same_v<T, int>)
        {
            obj = attr.as_int();
        }
        else if constexpr (is_same_v<T, unsigned int>)
        {
            obj = attr.as_uint();
        }
        else if constexpr (is_same_v<T, double>)
        {
            obj = attr.as_double();
        }
        else if constexpr (is_same_v<T, bool>)
        {
            obj = attr.as_bool();
        }
        else if constexpr (is_same_v<T, string>)
        {
            obj = attr.as_string();
        }
        else
        {
            throw runtime_error("Unable to parse attribute: " + name + " : " + typeid(T).name());
        }
    }

    template <typename T>
    void get_class(const xml_node &node, T &obj, const string &name)
    {
        auto child = node.child(name.c_str());

        if (child.empty())
        {
            string erro_msg = "ERROR: In Node: " + string(node.name()) + "\n Child not found: " + name;
            throw runtime_error(erro_msg);
        }

        from_xml(child, obj);
    }

    template <typename T>
    void from_string(const xml_node &node, T &obj, const string &name)
    {
        auto attr = node.attribute(name.c_str());
        if (attr.empty())
        {
            string erro_msg = "ERROR: In Node: " + string(node.name()) + "\n Attribute not found: " + name;
            throw runtime_error(erro_msg);
        }

        obj.from_string(attr.as_string());
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
        else if constexpr (is_base_of_v<IReadable, T>)
        {
            from_string(node, obj, name);
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
                      is_same_v<T, string> ||
                      is_base_of_v<IReadable, T>)
        {
            if (node.attribute(name.c_str()).empty())
            {
                obj = nullopt;
                return;
            }
        }
        else if constexpr (is_base_of_v<IXmlNode, T>)
        {
            if (node.child(name.c_str()).empty())
            {
                obj = nullopt;
                return;
            }
        }
        else
        {
            throw runtime_error("Unreachable : " + name + " : " + typeid(T).name());
        }
        
        obj = T();
        parse_xml(node, *obj, name);
    }

    template <typename T, typename = std::enable_if<is_vector_v<T>>>
    void parse_xml(const xml_node &node, vector<T> &obj, const string &name)
    {
        // cout << "parse_xml <vector>: " + name + " : " + typeid(T).name() << endl;
        if constexpr (is_base_of_v<IXmlNode, T>)
        {
            get_vector(node, obj, name);
        }
        else if constexpr (is_base_of_v<IReadable, T>)
        {
            throw runtime_error("Not implemented... : " + name + " : " + typeid(T).name());
        }
        else
        {
            throw runtime_error("Unreachable : " + name + " : " + typeid(T).name());
        }
    }

}