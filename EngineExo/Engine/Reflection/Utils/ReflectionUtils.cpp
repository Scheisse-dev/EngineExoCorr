#include "ReflectionUtils.h"
#include "../../PrimaryType/String/String.h"
#include "../../PrimaryType/Boolean/Boolean.h"

void Engine::Reflection::ReflectionUtils::SerializePrimaryType(std::ostream& _os, const Object* _obj, const PrimaryType::String& _fieldName)
{
    if (PrimaryType::String::IsNullOrEmpty(_fieldName))
        _os << "\"" << _obj->ToString().ToCstr() << "\"";
    else
        _os << "\"" << _fieldName.ToString().ToCstr() << "\" : \"" << _obj->ToString() << "\""; 
}
Engine::PrimaryType::String Engine::Reflection::ReflectionUtils::GetLine(std::istream& _is, const PrimaryType::String& _fieldName)
{
    std::string _line;
    while (std::getline(_is, _line))
    {
        if (!PrimaryType::String::IsNullOrEmpty(_fieldName))
        {
            if (_line.find(std::string("\"") + _fieldName.ToCstr() + "\"") != std::string::npos)
            {
                return _line.c_str();
            }
        }
        else {
            return _line.c_str();
        }
    }
    return "null";
}
