#pragma once

#include <sstream>
#include <fstream>
#include "json11.hpp"
#include "Logger.h"

namespace mini2d
{
class Utils
{
public:
    static std::string loadTextFile(const std::string& filename)
    {
        std::ifstream file(filename);
        std::stringstream buffer;
        buffer << file.rdbuf();
        return buffer.str();
    }

    static json11::Json parseJson(const std::string& input)
    {
        std::string errorOutput;
        auto parsedJson = json11::Json::parse(input, errorOutput);

        if (not errorOutput.empty())
        {
            LOG_ERROR("Failed while parsing json file: {}", errorOutput);
        }
        return parsedJson;
    }
};
}
