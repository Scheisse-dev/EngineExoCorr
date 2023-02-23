#pragma once
#include "../Object/Object.h"
#include "../PrimaryType/String/String.h"
#include <SFML/Graphics/Shape.hpp>
#include "../Component/Component.h"
#include "../PrimaryType/List/List.h"
#include "../Transform/Transform.h"

ENUM(PrimitiveType, Circle, Square)

namespace Engine
{
    namespace Window
    {
        class EngineWindow;
    }

    UCLASS()
    class GameObject : public Object
    {
        DECLARE_CLASS_INFO(GameObject, Object)
#pragma region f/p
    private:
        UPROPERTY() PrimaryType::List<Component*> components = PrimaryType::List<Component*>();
REGISTER_FIELD(components, &components, BindingFlags::NoPublic)
    protected:
        sf::Shape* shape = nullptr;
    public:
        UPROPERTY() PrimaryType::String name = "";
REGISTER_FIELD(name, &name, BindingFlags::Public)
        Transform* transform = nullptr;
#pragma endregion f/p
#pragma region constructor/destructor
    public:
        GameObject() = default;
        GameObject(const PrimaryType::String& _name);
        ~GameObject() override;
#pragma endregion constructor/destructor
#pragma region methods
    public:
        void AddComponent(Component* _component);
        PrimaryType::List<Component*> Components() const;
        sf::Shape* Shape() const;
        void SetColor(const sf::Color& _color) const;
        static GameObject* CreatePrimitive(const PrimitiveType& _type, const PrimaryType::String& _name);
        void Draw(const Window::EngineWindow* _window) const;
        void OnDeserializeFinish() override;
        template<typename T>
        T* AddComponent();
        template<typename T>
        T* GetComponent() const;
#pragma endregion methods
#pragma region operator
    public:
        GameObject& operator=(const GameObject& _other);
        PrimaryType::Boolean operator==(const GameObject& _other) const;
        PrimaryType::Boolean operator!=(const GameObject& _other) const;
#pragma endregion operator
    };
    template<typename T>
    T* GameObject::AddComponent()
    {
        static_assert(std::is_base_of_v<Component, T>, "T must be inherited of Component");
        T* _component = new T();
        _component->gameobject = this;
        components.Add(_component);
        return _component;
    }
    template<typename T>
    T* GameObject::GetComponent() const
    {
        const size_t _size = (size_t)components.Count();
        for (size_t i = 0; i < _size; ++i)
        {
            T* _result = dynamic_cast<T*>(components[i]);
            if (_result != nullptr) return _result;
        }
        return nullptr;
    }
}
