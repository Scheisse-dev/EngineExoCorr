#pragma once
#include "../Object/Object.h"
#include "../PrimaryType/Boolean/Boolean.h"

namespace Engine
{
    class GameObject;
    UCLASS()
    class Component : public Object
    {
        DECLARE_CLASS_INFO(Component, Object)
#pragma region f/p
    public:
        UPROPERTY() PrimaryType::Boolean enabled = true;
REGISTER_FIELD(enabled, &enabled, BindingFlags::Public)
        GameObject* gameobject = nullptr;
#pragma endregion f/p
#pragma region constructor
    public:
        Component() = default;
        ~Component() override = default;
#pragma endregion constructor
#pragma region operator
    public:
        Object& operator=(const Object* _obj) override;
#pragma endregion operator
    };
}
