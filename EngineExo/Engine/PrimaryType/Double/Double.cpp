#include "Double.h"
#include "../Boolean/Boolean.h"
#include "../String/String.h"

#pragma region f/p
const Engine::PrimaryType::Double Engine::PrimaryType::Double::Epsilon = 4.94065645841247E-324;
const Engine::PrimaryType::Double Engine::PrimaryType::Double::MinValue = -1.7976931348623157E+308;
const Engine::PrimaryType::Double Engine::PrimaryType::Double::MaxValue = 1.7976931348623157E+308;
const Engine::PrimaryType::Double Engine::PrimaryType::Double::PositiveInfinity = 1e+300 * 1e+300;
const Engine::PrimaryType::Double Engine::PrimaryType::Double::NegativeInfinity = -PositiveInfinity;
const Engine::PrimaryType::Double Engine::PrimaryType::Double::NaN = PositiveInfinity * 0.0;
#pragma endregion f/p
#pragma region constructor
Engine::PrimaryType::Double::Double(double _value) : super()
{
    value = _value;
}
Engine::PrimaryType::Double::Double(const Double& _copy) : super(_copy)
{
    value = _copy.value;
}
#pragma endregion constructor
#pragma region methods
Engine::PrimaryType::Double Engine::PrimaryType::Double::Parse(const String& _str)
{
    return std::stod(_str.ToCstr());
}
Engine::PrimaryType::Boolean Engine::PrimaryType::Double::TryParse(const String& _str, Double& _output)
{
    try
    {
        _output = std::stod(_str.ToCstr());
        return true;
    }
    catch (...)
    {
        _output = NaN;
        return false;
    }
}
Engine::PrimaryType::Boolean Engine::PrimaryType::Double::IsNaN(const Double& _value)
{
    return std::isnan(_value);
}
Engine::PrimaryType::Boolean Engine::PrimaryType::Double::IsEpsilon(const Double& _value)
{
    return _value == Epsilon;
}
Engine::PrimaryType::Boolean Engine::PrimaryType::Double::IsPositiveInfinity(const Double& _value)
{
    return _value == PositiveInfinity;
}
Engine::PrimaryType::Boolean Engine::PrimaryType::Double::IsNegativeInfinity(const Double& _value)
{
    return _value == NegativeInfinity;
}
void Engine::PrimaryType::Double::SerializeField(std::ostream& _os, const String& _fieldName, int _index)
{
    Reflection::ReflectionUtils::SerializePrimaryType(_os, this, _fieldName);
}
void Engine::PrimaryType::Double::DeSerializeField(std::istream& _is, const String& _fieldName)
{
    String _str = Reflection::ReflectionUtils::GetLine(_is, _fieldName);
    _str = _str.Replace("\"", "").Replace("\t", "").Replace(",", "").Replace(_fieldName, "").Replace(":", "").Trim();
    *this = std::stod(_str.ToCstr());
}
#pragma endregion methods
#pragma region override
Engine::PrimaryType::String Engine::PrimaryType::Double::ToString() const
{
    if (IsNaN(*this)) return "NaN";
    if (IsPositiveInfinity(*this)) return "Positive Infinity";
    if (IsNegativeInfinity(*this)) return "Negative Infinity";
    return std::to_string(value).c_str();
}
#pragma endregion override
#pragma region operator
Engine::PrimaryType::Double& Engine::PrimaryType::Double::operator=(const Double& _other)
{
    value = _other.value;
    return *this;
}
Engine::PrimaryType::Double::operator double()
{
    return value;
}
Engine::PrimaryType::Double::operator double() const
{
    return value;
}
Engine::PrimaryType::Double Engine::PrimaryType::Double::operator+(double _other) const
{
    return value + _other;
}
Engine::PrimaryType::Double Engine::PrimaryType::Double::operator-(double _other) const
{
    return value - _other;
}
Engine::PrimaryType::Double Engine::PrimaryType::Double::operator/(double _other) const
{
    return value / _other;
}
Engine::PrimaryType::Double Engine::PrimaryType::Double::operator*(double _other) const
{
    return value * _other;
}
Engine::PrimaryType::Double Engine::PrimaryType::Double::operator-() const
{
    return -value;
}
Engine::PrimaryType::Double& Engine::PrimaryType::Double::operator+=(double _other)
{
    value += _other;
    return *this;
}
Engine::PrimaryType::Double& Engine::PrimaryType::Double::operator-=(double _other)
{
    value -= _other;
    return *this;
}
Engine::PrimaryType::Double& Engine::PrimaryType::Double::operator/=(double _other)
{
    value /= _other;
    return *this;
}
Engine::PrimaryType::Double& Engine::PrimaryType::Double::operator*=(double _other)
{
    value *= _other;
    return *this;
}
Engine::PrimaryType::Boolean Engine::PrimaryType::Double::operator<(double _other) const
{
    return value < _other;
}
Engine::PrimaryType::Boolean Engine::PrimaryType::Double::operator<=(double _other) const
{
    return value <= _other;
}
Engine::PrimaryType::Boolean Engine::PrimaryType::Double::operator>(double _other) const
{
    return value > _other;
}
Engine::PrimaryType::Boolean Engine::PrimaryType::Double::operator>=(double _other) const
{
    return value >= _other;
}
Engine::PrimaryType::Boolean Engine::PrimaryType::Double::operator==(double _other) const
{
    return value == _other;
}
Engine::PrimaryType::Boolean Engine::PrimaryType::Double::operator!=(double _other) const
{
    return value != _other;
}
#pragma endregion operator
