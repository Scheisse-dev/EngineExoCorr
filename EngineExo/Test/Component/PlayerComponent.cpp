#include "PlayerComponent.h"

#include "../../Engine/GameObject/GameObject.h"
#include "../../Engine/Time/Time.h"

Test::PlayerComponent::PlayerComponent(const PlayerComponent& _copy) = default;


void Test::PlayerComponent::Update()
{
    Engine::PrimaryType::Vector2& _position = gameobject->transform->position;
    _position = Engine::PrimaryType::Vector2::MoveTowards(_position, Engine::PrimaryType::Vector2(100, 0), Engine::Time::deltaTime * 10.0f);
}
