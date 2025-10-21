
#pragma once

#include <string>
#include <string_view>

// If you import this file you will get the namespace

namespace ssp4cpp::utils
{
    static std::string escape_json_string(std::string_view component)
    {
        std::string escaped;
        escaped.reserve(component.size());

        for (const char c : component)
        {
            switch (c)
            {
            case '"':
                escaped.append("\\\"");
                break;
            case '\\':
                escaped.append("\\\\");
                break;
            case '\b':
                escaped.append("\\b");
                break;
            case '\f':
                escaped.append("\\f");
                break;
            case '\n':
                escaped.append("\\n");
                break;
            case '\r':
                escaped.append("\\r");
                break;
            case '\t':
                escaped.append("\\t");
                break;
            default:
                if (static_cast<unsigned char>(c) < 0x20)
                {
                    const unsigned char uc = static_cast<unsigned char>(c);
                    constexpr char hex_digits[] = "0123456789ABCDEF";
                    escaped.append("\\u00");
                    escaped.push_back(hex_digits[(uc >> 4) & 0x0F]);
                    escaped.push_back(hex_digits[uc & 0x0F]);
                }
                else
                {
                    escaped.push_back(c);
                }
                break;
            }
        }

        return escaped;
    }

}
