#pragma once
#include "../../PrimaryType/Boolean/Boolean.h"
#include "../../Utils/DebugMacro.h"


namespace Engine::Event
{
    template<typename Res, typename... Params>
    class Delegate : public Object
    {
        DECLARE_CLASS_INFO(Delegate, Object)
#pragma region f/p
    private:
        typedef Res (Object::*Function)(Params ...);
        Function function = nullptr;
        Object* instance = nullptr;
#pragma endregion f/p
#pragma region constructor
    public:
        Delegate(nullptr_t)
        {
            function = nullptr;
            instance = nullptr;
        }
        template<typename Class>
        Delegate(Class* _instance, Res (Class::*ptr)(Params ...))
        {
            checkBaseOf(Object, Class)
            instance = _instance;
            function = reinterpret_cast<Function>(ptr);
        }
#pragma endregion constructor
#pragma region methods
    public:
        void SetDynamic(nullptr_t)
        {
            function = nullptr;
            instance = nullptr;
        }
        template<typename Class>
        void SetDynamic(Class* _instance, Res (Class::*ptr)(Params ...))
        {
            checkBaseOf(Object, Class)
            instance = _instance;
            function = reinterpret_cast<Function>(ptr);
        }

        Res Invoke(Params ... _params)
        {
            return (instance->*function)(_params...);
        }

        PrimaryType::Boolean IsValid() const
        {
            return instance != nullptr && function != nullptr;
        }

        Object* Instance() const
        {
            return instance;
        }

        void* GetAddress() const
        {
            return (void*&)function;
        }

#pragma endregion methods
#pragma region operator
    public:
        PrimaryType::Boolean operator==(const Delegate& _other)
        {
            return GetAddress() == _other.GetAddress();
        }

        template<typename Class>
        PrimaryType::Boolean operator==(Res (Class::*ptr)(Params ...))
        {
            return GetAddress() == (void*&)ptr;
        }

        Delegate& operator=(const Delegate& _other)
        {
            instance = _other.instance;
            function = _other.function;
            return *this;
        }

        Delegate& operator=(nullptr_t)
        {
            function = nullptr;
            instance = nullptr;
            return *this;
        }

        Res operator()(Params ... _params)
        {
            return (instance->*function)(_params...);
        }

#pragma endregion operator
    };
}

template<typename Res, typename ... Params>
Engine::Event::Delegate<Res, Params...>::Delegate(const Delegate& _copy)
{
    function = _copy.function;
    instance = _copy.instance;
}
