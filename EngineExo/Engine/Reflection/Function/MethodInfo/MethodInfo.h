#pragma once
#include "../Function.h"
#include "../../Flags/BindingFlag.h"

namespace Engine
{
    class Object;
}

namespace Engine::Reflection
{
    template<typename Res, typename... Params>
    class MethodInfo : public Function
    {
#pragma region f/p
    private:
        typedef Res (Object::*FunctionType)(Params ...);
        typedef Res (*StaticFunctionType)(Params ...);
        FunctionType function = nullptr;
        StaticFunctionType staticFunction = nullptr;
        BindingFlags flags = BindingFlags::NoPublic;
#pragma endregion f/p
#pragma region constructor
    public:
        MethodInfo() = default;
        template<typename Class>
        MethodInfo(const std::string& _name, Res (Class::*ptr)(Params ...), const std::vector<ParameterInfo*>& _params, const BindingFlags& _flags)
            : Function(_name, _params)
        {
            if constexpr (!std::is_base_of_v<Object, Class>)
                throw std::exception("Class must be inherited of Object");
            function = reinterpret_cast<FunctionType>(ptr);
            flags = _flags;
        }
        
        MethodInfo(const std::string& _name, Res (*ptr)(Params ...), const std::vector<ParameterInfo*>& _params, const BindingFlags& _flags)
            : Function(_name, _params)
        {
            staticFunction = ptr;
            flags = _flags;
        }

#pragma endregion constructor
#pragma region methods
    public:
        BindingFlags Flags() const
        {
            return flags;
        }
        Res Invoke(Object* _instance, Params ... _params)
        {
            if (function != nullptr)
                return (_instance->*function)(_params...);
            return staticFunction(_params...);
        }
        void* GetAddress() const
        {
            if (function != nullptr)
                return (void*&)function;
            return (void*&)staticFunction;
        }
#pragma endregion methods
#pragma region operator
    public:
        bool operator==(nullptr_t)
        {
            return function == nullptr || staticFunction == nullptr;
        }
        bool operator!=(nullptr_t)
        {
            return function != nullptr || staticFunction != nullptr;
        }

        bool operator==(const MethodInfo& _other)
        {
            return GetAddress() == _other.GetAddress();
        }
        bool operator!=(const MethodInfo& _other)
        {
            return GetAddress() != _other.GetAddress();
        }

        template<typename Class>
        bool operator==(Res (Class::*ptr)(Params ...))
        {
            return GetAddress() == (void*&)ptr;
        }
        template<typename Class>
        bool operator!=(Res (Class::*ptr)(Params ...))
        {
            return GetAddress() != (void*&)ptr;
        }

#pragma endregion operator
    };
}
