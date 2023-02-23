#pragma once

#define REGISTER_TYPE(type) const size_t Type##type = TypeOfData::Register(#type, new type());

namespace Engine{ class Object; }
namespace Test{}

struct TypeOfData
{
    static inline std::map<std::string, Engine::Object*> Types = std::map<std::string, Engine::Object*>();

    static size_t Register(std::string typeName, Engine::Object* type)
    {
        if (Types.contains(typeName)) return Types.size();
        Types.insert(std::pair(typeName, type));
        return Types.size();
    }
};


template<typename T>
struct TypeOf
{
    static T* GetType()
    {
        return nullptr;
    }
};

#define Expose_TypeOf(type) \
    template<> \
    struct TypeOf<type> \
    {\
        static type* GetType()\
        {\
            return new type();\
        }\
    };
