#pragma once

#include <pugixml.hpp>

#include <optional>
#include <stdexcept>
#include <string>
#include <iostream>

// serialize object to xml

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
}