#pragma once

#include <sstream>
#include <fstream>

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
};
}
