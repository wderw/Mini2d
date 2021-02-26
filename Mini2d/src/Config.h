#pragma once

#include <map>
#include <string>
#include <any>
#include <memory>

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
        return std::any_cast<T>(config.at(key));
    }

private:
    std::map<std::string, ConfigValue> config;
};
}
