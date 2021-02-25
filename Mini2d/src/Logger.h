#pragma once

#include <memory>
#include "spdlog/spdlog.h"

namespace mini2d
{
class Logger
{
public:
    static void Initialize();
    inline static std::shared_ptr<spdlog::logger>& getLogger() { return logger; }

private:
    static std::shared_ptr<spdlog::logger> logger;
};
}

#define LOG_TRACE(...) ::mini2d::Logger::getLogger()->trace(__VA_ARGS__)
#define LOG_DEBUG(...) ::mini2d::Logger::getLogger()->debug(__VA_ARGS__)
#define LOG_INFO(...) ::mini2d::Logger::getLogger()->info(__VA_ARGS__)
#define LOG_WARN(...) ::mini2d::Logger::getLogger()->warn(__VA_ARGS__)
#define LOG_ERROR(...) ::mini2d::Logger::getLogger()->error(__VA_ARGS__)
#define LOG_CRITICAL(...) ::mini2d::Logger::getLogger()->critical(__VA_ARGS__)