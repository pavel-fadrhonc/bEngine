#pragma once

#include "Core.h"
#include "spdlog/spdlog.h" 

namespace bEngine
{
    class BENGINE_API Log
    {
    public:
        static void Init();

        inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() {return s_CoreLogger;}
        inline static std::shared_ptr<spdlog::logger>& GetClientLogger() {return s_ClientLogger;}
        
    private:
        static std::shared_ptr<spdlog::logger> s_ClientLogger;
        static std::shared_ptr<spdlog::logger> s_CoreLogger;
    };
}

// Core log macros
#define BE_CORE_TRACE(...)  ::bEngine::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define BE_CORE_INFO(...)   ::bEngine::Log::GetCoreLogger()->info(__VA_ARGS__)
#define BE_CORE_WARN(...)   ::bEngine::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define BE_CORE_ERROR(...)  ::bEngine::Log::GetCoreLogger()->error(__VA_ARGS__)
#define BE_CORE_FATAL(...)  ::bEngine::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client log macros
#define BE_CLIENT_TRACE(...)  ::bEngine::Log::GetClientLogger()->trace(__VA_ARGS__)
#define BE_CLIENT_INFO(...)   ::bEngine::Log::GetClientLogger()->info(__VA_ARGS__)
#define BE_CLIENT_WARN(...)   ::bEngine::Log::GetClientLogger()->warn(__VA_ARGS__)
#define BE_CLIENT_ERROR(...)  ::bEngine::Log::GetClientLogger()->error(__VA_ARGS__)
#define BE_CLIENT_FATAL(...)  ::bEngine::Log::GetClientLogger()->fatal(__VA_ARGS__)



