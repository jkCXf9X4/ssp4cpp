#pragma once

#include "common_log.hpp"

// Config.hpp
#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <optional>
#include <shared_mutex>
#include <nlohmann/json.hpp>

namespace ssp4cpp::sim::utils
{

    struct config_error : std::runtime_error
    {
        using std::runtime_error::runtime_error;
    };
    struct missing_key_error : config_error
    {
        using config_error::config_error;
    };
    struct type_error : config_error
    {
        using config_error::config_error;
    };

    class Config
    {
    public:
        static inline nlohmann::json data_{};

        // Load (or reload) JSON config from a file path.
        // Throws std::runtime_error on I/O or parse errors.
        static void loadFromFile(const std::string &path)
        {
            std::ifstream in(path);
            if (!in)
            {
                throw std::runtime_error("Config: cannot open file: " + path);
            }
            std::ostringstream buf;
            buf << in.rdbuf();
            nlohmann::json parsed = nlohmann::json::parse(buf.str());

            data_ = std::move(parsed);
        }

        static void data_available()
        {
            if (data_.is_null())
            {
                throw std::runtime_error("Config: data is not loaded");
            }
        }

        // Get a required value; throws if missing or type mismatch.
        template <class T>
        static T get(const std::string &dottedKey)
        {
            data_available();

            const nlohmann::json *node = resolvePath(dottedKey);
            if (!node || node->is_null())
            {
                throw missing_key_error("Config: missing key: " + dottedKey);
            }

            try
            {
                return node->get<T>();
            }
            catch (const std::exception &e)
            {
                throw type_error("Config: type error for key '" + dottedKey +
                                        "': " + std::string(e.what()));
            }
        }

        // Get with a default; returns defaultValue when key is missing.
        // Throws on type mismatch (to avoid silently bad configs).
        template <class T>
        static T getOr(const std::string &dottedKey, T defaultValue)
        {
            data_available();

            try
            {
                return get<T>(dottedKey);
            }
            catch (const missing_key_error &e)
            {
                return defaultValue;
            }
        }

        // Resolve "a.b.c" into a json node pointer (or nullptr if missing).
        static const nlohmann::json *resolvePath(const std::string &dottedKey)
        {
            const nlohmann::json *cur = &data_;
            if (dottedKey.empty())
            {
                return cur;
            }

            size_t pos = 0;
            while (cur && pos != std::string::npos)
            {
                size_t dot = dottedKey.find('.', pos);
                std::string key = (dot == std::string::npos)
                                      ? dottedKey.substr(pos)
                                      : dottedKey.substr(pos, dot - pos);

                // Allow array indices: "servers.0.host"
                if (!key.empty() && std::all_of(key.begin(), key.end(), ::isdigit))
                {
                    // numeric segment -> array index
                    size_t idx = static_cast<size_t>(std::stoul(key));
                    if (!cur->is_array() || idx >= cur->size())
                    {
                        return nullptr;
                    }
                    cur = &(*cur)[idx];
                }
                else
                {
                    if (!cur->is_object() || !cur->contains(key))
                    {
                        return nullptr;
                    }
                    cur = &(*cur)[key];
                }

                if (dot == std::string::npos)
                {
                    break;
                }
                pos = dot + 1;
            }
            return cur;
        }
    };

}