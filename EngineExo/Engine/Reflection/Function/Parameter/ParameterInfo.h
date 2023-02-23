#pragma once
#include <string>

#include "../../../Utils/Interface/Log/ILogger.h"

namespace Engine::Reflection
{
    class ParameterInfo : public Interface::ILogger
    {
#pragma region f/p
    private:
        std::string name = "";
        int position = 0;
#pragma endregion f/p
#pragma region constructor/destructor
    public:
        ParameterInfo() = default;
        ParameterInfo(const std::string& _name, int _position);
        virtual ~ParameterInfo() = default;
#pragma endregion constructor/destructor
#pragma region methods
    public:
        std::string Name() const;
        int Position() const;
#pragma endregion methods
#pragma region override
        PrimaryType::String ToString() const override;
#pragma endregion override
    };
}
