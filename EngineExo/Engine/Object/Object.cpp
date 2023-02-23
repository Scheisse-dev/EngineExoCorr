#include "Object.h"

#include <format>
#include <ranges>

#include "../PrimaryType/String/String.h"
#include "../PrimaryType/Boolean/Boolean.h"
#include "../Reflection/Flags/BindingFlag.h"
#include "../Utils/DebugMacro.h"
#include "../Reflection/Field/FieldInfo.h"
#pragma region constructor
Engine::Object::Object(const Object& _copy)
{
    flags = _copy.flags;
}
#pragma endregion constructor
#pragma region methods
Engine::PrimaryType::String Engine::Object::ToString() const
{
    return ClassName();
}
Engine::PrimaryType::String Engine::Object::ClassName() const
{
    PrimaryType::String _str = typeid(*this).name();
    _str = _str.Replace("class", "");
    return _str.SubString(_str.FindLastOf(':') + 1).Trim();
}

Engine::PrimaryType::Boolean Engine::Object::IsClass() const
{
    return flags == 0 || !(flags & (int)ClassFlags::Type);
}

Engine::Reflection::FieldInfo* Engine::Object::GetField(const PrimaryType::String& _name)
{
    check(fields.contains(_name.ToCstr()), std::format("[Object][Reflection] => {} doesn't exist in fields !", _name.ToCstr()), nullptr)
    return dynamic_cast<Reflection::FieldInfo*>(fields[_name.ToCstr()]);
}
std::vector<Engine::Reflection::FieldInfo*> Engine::Object::Fields() const
{
    std::vector<Reflection::FieldInfo*> _result = std::vector<Reflection::FieldInfo*>();
    for (Object* _o : fields | std::ranges::views::values)
    {
        Reflection::FieldInfo* _field = dynamic_cast<Reflection::FieldInfo*>(_o);
        if (_field == nullptr) continue;
        _result.push_back(_field);
    }
    return _result;
}
std::vector<Engine::Reflection::FieldInfo*> Engine::Object::Fields(const BindingFlags& _flags)
{
    std::vector<Reflection::FieldInfo*> _result = std::vector<Reflection::FieldInfo*>();
    for (Object* _o : fields | std::ranges::views::values)
    {
        Reflection::FieldInfo* _field = dynamic_cast<Reflection::FieldInfo*>(_o);
        if (_field == nullptr) continue;
        if (_field->Flags() & _flags)
            _result.push_back(_field);
    }
    return _result;
}
void Engine::Object::Serialize(std::ostream& _os, int _index)
{
    const std::vector<Reflection::FieldInfo*> _fields = Fields();
    const size_t _length = _fields.size();
    _os << std::string("\"") + ClassName().ToCstr() + "\" : " + "{\n";
    for (size_t i = 0; i < _length; i++)
    {
        _os << std::string(_index, '\t');
        if (_fields[i]->ReflectedObject() == nullptr)
            continue;
        if (_fields[i]->IsReflectedClass())
        {
            _fields[i]->ReflectedObject()->Serialize(_os, _index + 1);
        }
        else
        {
            _fields[i]->ReflectedObject()->SerializeField(_os, _fields[i]->Name(), _index);
        }
        if (i < _length - 1)
            _os << ",\n";
    }
    _os << "\n" << std::string(_index - 1, '\t') << "}";
}
void Engine::Object::DeSerialize(std::istream& _os)
{
    const std::vector<Reflection::FieldInfo*> _fields = Fields();
    const size_t _length = _fields.size();
    for (size_t i = 0; i < _length; i++)
    {
        if (_fields[i]->ReflectedObject() == nullptr) continue;
        if (_fields[i]->IsReflectedClass()) _fields[i]->ReflectedObject()->DeSerialize(_os);
        else _fields[i]->ReflectedObject()->DeSerializeField(_os, _fields[i]->Name());
    }
}
void Engine::Object::SerializeField(std::ostream& _os, const PrimaryType::String& _fieldName, int _index)
{
}

void Engine::Object::DeSerializeField(std::istream& _os, const PrimaryType::String& _fieldName)
{
}

size_t Engine::Object::InsertField(const std::string& _name, Object* _var, const BindingFlags& _flags)
{
    check(!fields.contains(_name), std::format("[Object][Reflection] => {} already register in fields", _name), fields.size())
    fields.insert(std::pair(_name, new Reflection::FieldInfo(_name.c_str(), _var, _flags)));
    return fields.size();
}
Engine::Object& Engine::Object::operator=(const Object* _obj)
{
    flags = _obj->flags;
    fields = _obj->fields;
    return *this;
}

int Engine::Object::RegisterClassInfo(int _flags)
{
    return flags = _flags;
}

#pragma endregion methods
