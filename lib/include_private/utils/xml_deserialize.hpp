#pragma once

#include "ssp4cpp/utils/interface.hpp"
#include "ssp4cpp/utils/string.hpp"

#include <pugixml.hpp>

#include <optional>
#include <stdexcept>
#include <string>
#include <iostream>
#include <vector>
#include <format>
#include <memory> // for std::unique_ptr, std::make_unique

// deserialize xml to object

namespace ssp4cpp::utils::xml
{
    using namespace pugi;

    using namespace ssp4cpp::utils::interfaces;

    // Concepts
    template <typename T>
    concept XmlNodeLike = std::derived_from<std::remove_cvref_t<T>, interfaces::IXmlNode>;

    template <typename T>
    concept EnumLike = std::derived_from<std::remove_cvref_t<T>, interfaces::IEnum>;

    namespace detail
    {
        template <class T>
        struct attr_parser; // primary template = unsupported

        template <>
        struct attr_parser<int>
        {
            static int parse(pugi::xml_attribute a) { return a.as_int(); }
        };

        template <>
        struct attr_parser<unsigned>
        {
            static unsigned parse(pugi::xml_attribute a) { return a.as_uint(); }
        };

        template <>
        struct attr_parser<double>
        {
            static double parse(pugi::xml_attribute a) { return a.as_double(); }
        };

        template <>
        struct attr_parser<bool>
        {
            static bool parse(pugi::xml_attribute a) { return a.as_bool(); }
        };

        template <>
        struct attr_parser<std::string>
        {
            static std::string parse(pugi::xml_attribute a) { return std::string(a.as_string()); }
        };

        template <class T>
        inline constexpr bool has_attr_parser_v =
            requires(pugi::xml_attribute a) { attr_parser<T>::parse(a); };

    } // namespace detail


    // Helper
    inline std::string parents_to_string(const pugi::xml_node &node)
    {
        std::string s;
        s.reserve(128);

        for (auto p = node; p; p = p.parent())
        {
            s += p.name();

            if (auto attr = p.attribute("name"))
            {
                s += ':';
                s += attr.as_string();
            }
            s += '/';
        }
        return s;
    }

    inline pugi::xml_attribute get_attrib(const xml_node &node, const std::string &name, bool required = false)
    {
        auto attr = node.attribute(name.c_str());
        if (attr.empty() && required)
        {
            std::string msg = "ERROR: In Node: " + parents_to_string(node) + "\n Attribute not found: " + name;
            throw std::runtime_error(msg);
        }
        return attr;
    }

    inline pugi::xml_node get_child(const xml_node &node, const std::string &name, bool required = false)
    {
        auto child = node.child(name.c_str());
        if (child.empty() && required)
        {
            auto msg = std::format("[{}] ERROR: In node: {}\n  Child not found: {}", __func__, parents_to_string(node), name);
            throw std::runtime_error(msg);
        }
        return child;
    }
    
    // Parse attribute
    template <class T>
    T parse_attr_or_throw(pugi::xml_attribute a, const std::string &name)
    {
        if constexpr (!detail::has_attr_parser_v<T>)
        {
            throw std::runtime_error(std::format(
                "[{}] Unsupported attribute type for '{}': {}",
                __func__, name, typeid(T).name()));
        }
        return detail::attr_parser<T>::parse(a);
    }

    template <typename T>
    void get_attribute(const xml_node &node, T &obj, const std::string &name)
    {
        auto attr = get_attrib(node, name, /*required=*/true);
        obj = parse_attr_or_throw<T>(attr, name);
    }

    /**
     * @brief Parse an optional XML attribute or child element.
     */
    template <typename T>
    void get_optional_attribute(const xml_node &node, std::optional<T> &obj, const std::string &name)
    {
        auto attr = get_attrib(node, name, /*required=*/false);
        if (attr.empty())
        {
            obj.reset();
            return;
        }
        obj = parse_attr_or_throw<T>(attr, name);
    }

    // Parse attribute
    template <EnumLike T>
    void get_enum(const xml_node &node, T &obj, const std::string &name)
    {
        auto attr = get_attrib(node, name, /*required=*/true);

        obj.from_string(attr.as_string());
    }

    /**
     * @brief Parse an optional XML attribute or child element.
     */
    template <EnumLike T>
    void get_optional_enum(const xml_node &node, std::optional<T> &obj, const std::string &name)
    {
        auto attr = get_attrib(node, name, /*required=*/false);
        if (attr.empty())
        {
            obj.reset();
            return;
        }
        T t{};
        t.from_string(attr.as_string());
        obj = std::move(t);
    }

    // Parse class
    template <XmlNodeLike T>
    void get_class(const xml_node &node, T &obj, const std::string &name)
    {
        auto child = get_child(node, name, /*required=*/true);
        from_xml(child, obj);
    }

    // Optional attribute/child: sets std::optional<T>
    template <XmlNodeLike T>
    void get_optional_class(const xml_node &node, std::optional<T> &obj, const std::string &name)
    {
        auto child = get_child(node, name, /*required=*/false);
        if (child.empty())
        {
            obj.reset();
            return;
        }

        T tmp{};
        from_xml(child, tmp);
        obj = std::move(tmp);
    }

    // Parse vector
    template <XmlNodeLike T>
    void get_vector(const xml_node &node, std::vector<T> &list, const std::string &name)
    {
        // cout << "get_vector: " << name + " : " + typeid(T).name() << endl;
        for (auto child : node.children(name.c_str()))
        {
            T t{};
            from_xml(child, t);
            list.emplace_back(std::move(t));
        }
    }

    template <typename T>
    void get_readable_vector(const xml_node &node, std::vector<T> &list, const std::string &name, const std::string &del)
    {
        auto a = get_attrib(node, name, /*required=*/false);
        if (a.empty())
        {
            // std::cout << "get_vector: " << name + " : " + typeid(T).name() << std::endl;
            list = std::vector<T>();
        }
        else
        {
            // std::cout << "get_vector: " << name + " : '" + a.as_string() << "'" << std::endl;
            list = str::from_strs<T>(std::string(a.as_string()), del);
        }
    }

    template <typename T>
    std::unique_ptr<T> parse_file(const std::string &fileName, const std::string &root_name)
    {
        pugi::xml_document doc;
        pugi::xml_parse_result result = doc.load_file(fileName.c_str());
        if (!result)
        {
            throw std::runtime_error(std::format("Unable to load xml {}", root_name));
        }
        auto root = doc.child(root_name.c_str());
        if (!root)
        {
            throw std::runtime_error(std::format("Root node '{}' not found", root_name));
        }

        std::unique_ptr<T> obj = std::make_unique<T>();

        from_xml(root, *obj);

        return obj;
    }
}
