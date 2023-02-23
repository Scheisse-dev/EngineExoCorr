#pragma once
#include "../Exception/Exception.h"
#include "Console/Console.h"
#include <format>

#define LOG(msg) Engine::Utils::Console::Log(msg);
#define LOG_FORMAT(msg, ...) Engine::Utils::Console::Log(std::format(msg, __VA_ARGS__));
#define LOG_WARNING(msg) Engine::Utils::Console::LogWarning(msg);
#define LOG_WARNING_FORMAT(msg, ...) Engine::Utils::Console::LogWarning(std::format(msg, __VA_ARGS__));
#define LOG_ERROR(msg) Engine::Utils::Console::LogError(msg);
#define LOG_ERROR_FORMAT(msg, ...) Engine::Utils::Console::LogError(std::format(msg, __VA_ARGS__));

#define checkLow(condition, msg) \
    if (!condition)\
    {\
        LOG_ERROR(msg);\
        return;\
    }

#define check(condition, msg, result)\
    if (!condition)\
    {\
        LOG_ERROR(msg);\
        return result;\
    }

#define checkBaseOf(a, b)\
    if constexpr (!std::is_base_of_v<a, b>)\
    {\
        LOG_ERROR(#b " must be inherited of " #a);\
        return;\
    }
