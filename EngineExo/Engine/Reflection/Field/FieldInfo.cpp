#include "FieldInfo.h"
#include "../../PrimaryType/Boolean/Boolean.h"
#pragma region constructor
Engine::Reflection::FieldInfo::FieldInfo(const PrimaryType::String& _name, Object* _reflectedObject, BindingFlags _flags)
{
    name = _name;
    reflectedObject = _reflectedObject;
    flags = _flags;
}

Engine::Reflection::FieldInfo::FieldInfo(const FieldInfo& _copy)
    : super(_copy)
{
    name = _copy.name;
    reflectedObject = _copy.reflectedObject;
    flags = _copy.flags;
}

#pragma endregion constructor
#pragma region methods
Engine::PrimaryType::Boolean Engine::Reflection::FieldInfo::IsPublic() const
{
    return flags & BindingFlags::Public;
}
Engine::PrimaryType::Boolean Engine::Reflection::FieldInfo::IsPrivate() const
{
    return flags & BindingFlags::NoPublic;
}
Engine::PrimaryType::Boolean Engine::Reflection::FieldInfo::IsStatic() const
{
    return flags & BindingFlags::Static;
}
Engine::PrimaryType::Boolean Engine::Reflection::FieldInfo::IsArray() const
{
    return flags & BindingFlags::Array;
}
Engine::PrimaryType::Boolean Engine::Reflection::FieldInfo::IsReflectedClass() const
{
    return reflectedObject->IsClass();
}
Engine::PrimaryType::String Engine::Reflection::FieldInfo::Name() const
{
    return name;
}
BindingFlags Engine::Reflection::FieldInfo::Flags() const
{
    return flags;
}
Engine::Object* Engine::Reflection::FieldInfo::ReflectedObject()
{
    return reflectedObject;
}
#pragma endregion methods
#pragma region override
Engine::PrimaryType::String Engine::Reflection::FieldInfo::ToString() const
{
    return reflectedObject == nullptr ? PrimaryType::String("nullptr") : reflectedObject->ToString();
}
Engine::Object& Engine::Reflection::FieldInfo::operator=(const Object* _obj)
{
    return (*reflectedObject) = _obj;
}
#pragma endregion override
