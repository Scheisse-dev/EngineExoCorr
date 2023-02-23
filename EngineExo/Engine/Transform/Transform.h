#pragma once
#include "../Component/Component.h"
#include "../PrimaryType/Vector/Vector2.h"

namespace Engine
{
    UCLASS()
    class Transform : public Component
    {
        DECLARE_CLASS_INFO(Transform, Component)
#pragma region f/p
    public:
        UPROPERTY() PrimaryType::Vector2 position = PrimaryType::Vector2(0, 0);
REGISTER_FIELD(position, &position, BindingFlags::Public)
#pragma endregion f/p
        Transform() = default;
#pragma region operator
    public:
        Transform& operator=(const Transform& _other);
        Object& operator=(const Object* _other) override;
#pragma endregion operator
    };
}
