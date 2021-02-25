#include "Logger.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace mini2d
{
std::shared_ptr<spdlog::logger> Logger::logger;

void Logger::Initialize()
{
    spdlog::set_pattern("%^[%T] %n: %v%$");
    logger = spdlog::stdout_color_mt("APP");
    logger->set_level(spdlog::level::trace);

    LOG_INFO("Spdlog initialized.");
}
}
