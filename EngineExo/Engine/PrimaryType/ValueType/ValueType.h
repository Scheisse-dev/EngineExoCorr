#pragma once
#include "../../Object/Object.h"
#include "../../Reflection/Utils/ReflectionUtils.h"

namespace Engine::PrimaryType
{
    class ValueType : public Object
    {
        DECLARE_CLASS_INFO_FLAGS(ValueType, Object, ClassFlags::Type)
#pragma region constructor/destructor
    public:
        ValueType() = default;
        ~ValueType() override = default;
#pragma endregion constructor/destructor
#pragma region operator
    public:
        Object& operator=(const Object* _other) override
        {
            return super::operator=(_other);
        }
#pragma endregion operator
    };
}
