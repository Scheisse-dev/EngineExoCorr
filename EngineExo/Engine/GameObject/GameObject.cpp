#include "GameObject.h"
#include "../PrimaryType/Boolean/Boolean.h"
#include "../Utils/DebugMacro.h"
#include "../Window/Engine/EngineWindow.h"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "../Manager/GameObject/GameObjectManager.h"

#pragma region constructor/destructor
Engine::GameObject::GameObject(const PrimaryType::String& _name) : super()
{
    name = _name;
    transform = AddComponent<Transform>();
    Manager::GameObjectManager::Instance()->Register(this);
}
Engine::GameObject::GameObject(const GameObject& _copy) : super(_copy)
{
    shape = _copy.shape;
    name = _copy.name;
    transform = _copy.transform;
    Manager::GameObjectManager::Instance()->Register(this);
}
Engine::GameObject::~GameObject()
{
    delete shape;
    shape = nullptr;
    Manager::GameObjectManager::Instance()->UnRegister(this);
}
#pragma endregion constructor/destructor
#pragma region methods
void Engine::GameObject::AddComponent(Component* _component)
{
    _component->gameobject = this;
    components.Add(_component);
}

Engine::PrimaryType::List<Engine::Component*> Engine::GameObject::Components() const
{
    return components;
}

sf::Shape* Engine::GameObject::Shape() const
{
    return shape;
}
void Engine::GameObject::SetColor(const sf::Color& _color) const
{
    checkLow((shape != nullptr), "[GameObject] => shape is nullptr")
    shape->setFillColor(_color);
}
Engine::GameObject* Engine::GameObject::CreatePrimitive(const PrimitiveType& _type, const PrimaryType::String& _name)
{
    GameObject* _result = new GameObject(_name);
    switch (_type)
    {
    case PrimitiveType::Circle:
        _result->shape = new sf::CircleShape(25.0f);
        break;
    case PrimitiveType::Square:
        _result->shape = new sf::RectangleShape(sf::Vector2f(25.0f, 25.0f));
        break;
    }
    return _result;
}
void Engine::GameObject::Draw(const Window::EngineWindow* _window) const
{
    if (shape == nullptr) return;
    shape->setPosition(transform->position);
    _window->Draw(shape);
}
void Engine::GameObject::OnDeserializeFinish()
{
    for (Component*& _component : components)
        _component->gameobject = this;
}
#pragma endregion methods
#pragma region operator
Engine::GameObject& Engine::GameObject::operator=(const GameObject& _other)
{
    name = _other.name;
    shape = _other.shape;
    return *this;
}
Engine::PrimaryType::Boolean Engine::GameObject::operator==(const GameObject& _other) const
{
    return name == _other.name && shape == _other.shape;
}
Engine::PrimaryType::Boolean Engine::GameObject::operator!=(const GameObject& _other) const
{
    return !this->operator==(_other);
}
#pragma endregion operator