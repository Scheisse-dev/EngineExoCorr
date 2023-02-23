#pragma once

namespace Engine::PrimaryType
{
    class String;
}
namespace Engine::Interface
{
    class ILogger
    {
    public:
        virtual ~ILogger() = default;
        virtual PrimaryType::String ToString() const = 0;
    };
}
