#pragma once
#include <fstream>

namespace Engine
{
    class Object;
}
namespace Engine::PrimaryType
{
    class String;
    class Boolean;
}

namespace Engine::Reflection
{
    class ReflectionUtils
    {
    public:

        static void SerializePrimaryType(std::ostream& _os, const Object* _obj, const PrimaryType::String& _fieldName);
        
        static PrimaryType::String GetLine(std::istream& _is, const PrimaryType::String& _fieldName);
    };
}
