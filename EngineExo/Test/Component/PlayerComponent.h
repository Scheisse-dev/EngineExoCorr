#pragma once
#include "../../Engine/Component/Component.h"

namespace Engine
{
    class GameObject;
}
namespace Test
{
    UCLASS()
    class PlayerComponent : public Engine::Component
    {
        DECLARE_CLASS_INFO(PlayerComponent, Component)
    public:
        PlayerComponent() = default;
        void Update();
    };
}
