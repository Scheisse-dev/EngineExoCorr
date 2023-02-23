#include "Integer.h"

#include "../../Utils/Template/Template.h"
#include "../Boolean/Boolean.h"
#include "../String/String.h"

#pragma region f/p
const Engine::PrimaryType::Integer Engine::PrimaryType::Integer::MinValue = INT_MIN;
const Engine::PrimaryType::Integer Engine::PrimaryType::Integer::MaxValue = INT_MAX;
#pragma endregion f/p

#pragma region constructor
Engine::PrimaryType::Integer::Integer(int _value) : super()
{
    value = _value;
}
Engine::PrimaryType::Integer::Integer(const Integer& _copy) : super(_copy)
{
    value = _copy.value;
}
#pragma endregion constructor
#pragma region methods
Engine::PrimaryType::Integer Engine::PrimaryType::Integer::Parse(const String& _str)
{
    return std::stoi(_str.ToCstr());
}
Engine::PrimaryType::Boolean Engine::PrimaryType::Integer::TryParse(const String& _str, Integer& _output)
{
    try
    {
        _output = std::stoi(_str.ToCstr());
        return true;
    }
    catch (...)
    {
        _output = -1;
        return false;
    }
}
#pragma endregion methods
#pragma region override
Engine::PrimaryType::String Engine::PrimaryType::Integer::ToString() const
{
    return std::to_string(value).c_str();
}

void Engine::PrimaryType::Integer::SerializeField(std::ostream& _os, const String& _fieldName, int _index)
{
    Reflection::ReflectionUtils::SerializePrimaryType(_os, this, _fieldName);
}
void Engine::PrimaryType::Integer::DeSerializeField(std::istream& _is, const PrimaryType::String& _fieldName)
{
    String _str = Reflection::ReflectionUtils::GetLine(_is, _fieldName);
    _str = _str.Replace("\"", "").Replace("\t", "").Replace(",", "").Replace(_fieldName, "").Replace(":", "").Trim();
    *this = std::stoi(_str.ToCstr());
}

Engine::PrimaryType::Integer& Engine::PrimaryType::Integer::operator=(const Integer& _other)
{
    value = _other.value;
    return *this;
}

Engine::Object& Engine::PrimaryType::Integer::operator=(const Object*& _other)
{
    if (!IsSame<Integer>(_other)) return *this;
    super::operator=(_other);
    const Integer* _integer = dynamic_cast<const Integer*>(_other);
    value = _integer->value;
    return *this;
}
#pragma endregion override

#pragma region operator
Engine::PrimaryType::Integer::operator int()
{
    return value;
}
Engine::PrimaryType::Integer::operator int() const
{
    return value;
}
Engine::PrimaryType::Boolean Engine::PrimaryType::Integer::operator>(int _other) const
{
    return value > _other;
}
Engine::PrimaryType::Boolean Engine::PrimaryType::Integer::operator>=(int _other) const
{
    return value >= _other;
}
Engine::PrimaryType::Boolean Engine::PrimaryType::Integer::operator<(int _other) const
{
    return value < _other;
}
Engine::PrimaryType::Boolean Engine::PrimaryType::Integer::operator<=(int _other) const
{
    return value <= _other;
}
Engine::PrimaryType::Boolean Engine::PrimaryType::Integer::operator==(int _other) const
{
    return value == _other;
}
Engine::PrimaryType::Boolean Engine::PrimaryType::Integer::operator!=(int _other) const
{
    return value != _other;
}
Engine::PrimaryType::Integer Engine::PrimaryType::Integer::operator+(int _other) const
{
    return value + _other;
}
Engine::PrimaryType::Integer Engine::PrimaryType::Integer::operator-(int _other) const
{
    return value - _other;
}
Engine::PrimaryType::Integer Engine::PrimaryType::Integer::operator*(int _other) const
{
    return value * _other;
}
Engine::PrimaryType::Integer Engine::PrimaryType::Integer::operator/(int _other) const
{
    return value / _other;
}
Engine::PrimaryType::Integer Engine::PrimaryType::Integer::operator%(int _other) const
{
    return value % _other;
}
Engine::PrimaryType::Integer& Engine::PrimaryType::Integer::operator+=(int _other)
{
    value += _other;
    return *this;
}
Engine::PrimaryType::Integer& Engine::PrimaryType::Integer::operator-=(int _other)
{
    value -= _other;
    return *this;
}
Engine::PrimaryType::Integer& Engine::PrimaryType::Integer::operator*=(int _other)
{
    value *= _other;
    return *this;
}
Engine::PrimaryType::Integer& Engine::PrimaryType::Integer::operator/=(int _other)
{
    value /= _other;
    return *this;
}
Engine::PrimaryType::Integer& Engine::PrimaryType::Integer::operator%=(int _other)
{
    value %= _other;
    return *this;
}
Engine::PrimaryType::Integer& Engine::PrimaryType::Integer::operator++()
{
    ++value;
    return *this;
}
Engine::PrimaryType::Integer& Engine::PrimaryType::Integer::operator--()
{
    --value;
    return *this;
}
Engine::PrimaryType::Integer Engine::PrimaryType::Integer::operator++(int)
{
    const int _result = value;
    operator++();
    return _result;
}
Engine::PrimaryType::Integer Engine::PrimaryType::Integer::operator--(int)
{
    const int _result = value;
    operator--();
    return _result;
}
Engine::PrimaryType::Integer Engine::PrimaryType::Integer::operator-() const
{
    return -value;
}
#pragma endregion operator
