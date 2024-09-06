
// #include "xml_misc.hpp"
#include <pugixml.hpp>
#include <optional>
#include <stdexcept>
#include <string>

namespace ssp4cpp::xml
{
    using namespace std;

    // set_attribute

    // template <typename T>
    // void set_attribute(pugi::xml_node &node, const char *name, const T &value)
    // {
    //     node.append_attribute(name).set_value(value->c_str());
    // }


    // template <typename T>
    // void set_optional_attribute(pugi::xml_node &node, const char *name, const optional<T> &value)
    // {
    //     if (value)
    //     {
    //         set_attribute<T>(node, name, value);
    //     }
    // }

    // get attribute

    template <typename T>
    T get_attribute(const pugi::xml_node &node, const string &name)
    {
        if constexpr (is_same_v<T, int>)
        {
            return node.attribute(name.c_str()).as_int();
        }
        else if constexpr (is_same_v<T, unsigned int>)
        {
            return node.attribute(name.c_str()).as_uint();
        }
        else if constexpr (is_same_v<T, double>)
        {
            return node.attribute(name.c_str()).as_double();
        }
        else if constexpr (is_same_v<T, bool>)
        {
            return node.attribute(name.c_str()).as_bool();
        }
        else if constexpr (is_same_v<T, string>)
        {
            return node.attribute(name.c_str()).as_string();
        }
        else
        {
            throw runtime_error("Unable to parse attribute: " + name);
        }
    }

    template <typename T>
    optional<T> get_optional_attribute(const pugi::xml_node &node, const string &name)
    {
        if (node.attribute(name.c_str()).empty())
        {
            return nullopt;
        }
        return get_attribute<T>(node, name);
    }

    // set_child

    // template <typename T>
    // void set_child_value(pugi::xml_node &node, const char *name, const T &value)
    // {
    //     node.append_child(name).text().set(value->c_str());
    // }

    // template <typename T>
    // void set_optional_child_value(pugi::xml_node &node, const char *name, const optional<T> &value)
    // {
    //     if (value)
    //     {
    //         set_child_value<T>(node, name, value);
    //     }
    // }

    // get_child

    template <typename T>
    optional<T> get_child_value(const pugi::xml_node &node, const char *name)
    {
        return node.child(name).text().as_string();
    }

    template <typename T>
    optional<T> get_optional_child_value(const pugi::xml_node &node, const char *name)
    {
        auto child = node.child(name);
        if (child)
        {
            return child.text().as_string();
        }
        return {};
    }

}