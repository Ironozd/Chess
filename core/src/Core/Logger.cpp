#include "Logger.h"

namespace Chess
{
    std::shared_ptr<spdlog::logger> Logger::s_Logger;

    void Logger::Initialize()
    {
        auto ConsoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        ConsoleSink->set_level(spdlog::level::trace);
        ConsoleSink->set_pattern("[%T] %^[%l] %v%$");
        
        auto FileSink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("Chess.log", true);
        FileSink->set_level(spdlog::level::trace);
        FileSink->set_pattern("[%T] %^[%l] %v%$");

        s_Logger = std::make_shared<spdlog::logger>("Chess", spdlog::sinks_init_list{ FileSink ,ConsoleSink });
        s_Logger->set_level(spdlog::level::trace);
        spdlog::set_level(spdlog::level::trace);
    }
}