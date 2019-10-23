#pragma once

#include "spdlog/spdlog.h"

#include <memory>

class Log
{
public:
    static void Init();

    inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
    inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

private:
    static std::shared_ptr<spdlog::logger> s_CoreLogger;
    static std::shared_ptr<spdlog::logger> s_ClientLogger;
};

#define LOG_CORE_TRACE(...) ::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define LOG_CORE_INFO(...) ::Log::GetCoreLogger()->info(__VA_ARGS__)
#define LOG_CORE_WARN(...) ::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define LOG_CORE_ERROR(...) ::Log::GetCoreLogger()->error(__VA_ARGS__)
#define LOG_CORE_FATAL(...) ::Log::GetCoreLogger()->critical(__VA_ARGS__)

#define LOG_TRACE(...) ::Log::GetClientLogger()->trace(__VA_ARGS__)
#define LOG_INFO(...) ::Log::GetClientLogger()->info(__VA_ARGS__)
#define LOG_WARN(...) ::Log::GetClientLogger()->warn(__VA_ARGS__)
#define LOG_ERROR(...) ::Log::GetClientLogger()->error(__VA_ARGS__)
#define LOG_FATL(...) ::Log::GetClientLogger()->critical(__VA_ARGS__)
