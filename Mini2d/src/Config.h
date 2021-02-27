#pragma once

#include <map>
#include <string>
#include <any>
#include <memory>
#include "Logger.h"

namespace mini2d
{
class Config
{
public:
    using ConfigValue = std::any;
    template <typename T>
    void set(std::string key, T value)
    {
        config.emplace(key, ConfigValue(value));
    }

    template <typename T>
    T get(const std::string& key) const
    {
        try
        {
            return std::any_cast<T>(config.at(key));
        }
        catch (std::exception& e)
        {
            LOG_ERROR("Bad any cast when trying to access: {}", key);
            throw e;
        }
    }

private:
    std::map<std::string, ConfigValue> config;
};
}
