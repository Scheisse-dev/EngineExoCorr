#include "ParameterInfo.h"
#include <format>
#include "../../../PrimaryType/String/String.h"

#pragma region constructor
Engine::Reflection::ParameterInfo::ParameterInfo(const std::string& _name, int _position)
{
    name = _name;
    position = _position;
}
#pragma endregion constructor
#pragma region methods
std::string Engine::Reflection::ParameterInfo::Name() const
{
    return name;
}
int Engine::Reflection::ParameterInfo::Position() const
{
    return position;
}
Engine::PrimaryType::String Engine::Reflection::ParameterInfo::ToString() const
{
    return std::format("Name: {}, Position: {}", name, position).c_str();
}
#pragma endregion methods
