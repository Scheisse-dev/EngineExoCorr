#include "Boolean.h"
#include "../String/String.h"
#pragma region constructor
Engine::PrimaryType::Boolean::Boolean(bool _value) : super()
{
    value = _value;
}
Engine::PrimaryType::Boolean::Boolean(const Boolean& _copy) : super(_copy)
{
    value = _copy.value;
}
#pragma region constructor
#pragma region override
Engine::PrimaryType::String Engine::PrimaryType::Boolean::ToString() const
{
    return value ? "true" : "false";
}
void Engine::PrimaryType::Boolean::SerializeField(std::ostream& _os, const PrimaryType::String& _fieldName, int _index)
{
    Reflection::ReflectionUtils::SerializePrimaryType(_os, this, _fieldName);
}
void Engine::PrimaryType::Boolean::DeSerializeField(std::istream& _is, const PrimaryType::String& _fieldName)
{
    String _str = Reflection::ReflectionUtils::GetLine(_is, _fieldName);
    _str = _str.Replace("\"", "").Replace("\t", "").Replace(",", "").Replace(_fieldName, "").Replace(":", "").Trim();
    *this = _str == "true";
}
#pragma endregion override
#pragma region operator
Engine::PrimaryType::Boolean& Engine::PrimaryType::Boolean::operator=(const Boolean& _other)
{
    value = _other.value;
    return *this;
}
Engine::PrimaryType::Boolean Engine::PrimaryType::Boolean::operator!() const
{
    return !value;
}
Engine::PrimaryType::Boolean::operator bool()
{
    return value;
}
Engine::PrimaryType::Boolean::operator bool() const
{
    return value;
}
#pragma endregion operator
