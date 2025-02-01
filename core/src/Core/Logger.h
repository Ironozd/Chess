#pragma once
#include <memory>
#include <iostream>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

/**
 * @brief Logger file
 * 
 * @note Inspired by TheCherno.
 * 
 * @todo Only include LOGGER functions during DEBUG configuration.
 */

namespace Application
{

    class Logger
    {
    public:
        static void Initialize();

        static std::shared_ptr<spdlog::logger>& GetLogger() { return s_Logger; }
    private:
        static std::shared_ptr<spdlog::logger> s_Logger;
    };

}
    
#define LOG_INFO(...) ::Application::Logger::GetLogger()->info(__VA_ARGS__)
#define LOG_WARN(...) ::Application::Logger::GetLogger()->warn(__VA_ARGS__)
#define LOG_CRITICAL(...) ::Application::Logger::GetLogger()->critical(__VA_ARGS__)
#define LOG_ERROR(...) ::Application::Logger::GetLogger()->error(__VA_ARGS__)   