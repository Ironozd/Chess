#pragma once
#include <memory>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

namespace Chess
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
    
#define LOG_INFO(...) ::Chess::Logger::GetLogger()->info(__VA_ARGS__)
#define LOG_WARN(...) ::Chess::Logger::GetLogger()->warn(__VA_ARGS__)
#define LOG_CRITICAL(...) ::Chess::Logger::GetLogger()->critical(__VA_ARGS__)
#define LOG_ERROR(...) ::Chess::Logger::GetLogger()->error(__VA_ARGS__)