#pragma once
#include "../../Event/Action/ActionInternal.h"
#include "../Element/UIElement.h"
#include "../Interface/IPointerClickHandler.h"
#include "../Interface/IPointerEnterHandler.h"
#include "../Interface/IPointerExitHandler.h"

namespace Engine::UI
{
    class Button : public UIElement, public IPointerClickHandler, public IPointerEnterHandler, public IPointerExitHandler
    {
        DECLARE_CLASS_INFO(Button, UIElement)
#pragma region f/p
    private:
        float width = 100.0f;
        float height = 40.0f;
        sf::Text text = sf::Text();
        sf::Color baseColor = sf::Color::White;
        sf::Color enterColor = sf::Color(189, 195, 199);
        Action<> onClick = nullptr;
#pragma endregion f/p
#pragma region constructor/destructor
    public:
        Button() = default;
        Button(const std::string& _text, float _width, float _height);
        Button(const std::string& _text, float _width, float _height, Action<> _onClick);
#pragma endregion constructor/destructor
#pragma region methods
    public:
        template<typename Class>
        void AddListener(Class* _instance, void(Class::*ptr)())
        {
            onClick.AddDynamic(_instance, ptr);
        }
        template<typename Class>
        void RemoveListener(Class* _instance, void(Class::*ptr)())
        {
            onClick.RemoveDynamic(_instance, ptr);
        }
        void SetBackgroundColor(const sf::Color& _color);
        
#pragma endregion methods
#pragma region override
    public:
        void OnPointerEnter() override;
        void OnPointerExit() override;
        void SetPosition(const PrimaryType::Vector2& _position) override;
        void Draw(sf::RenderWindow* _window) override;
        void OnPointerClick(const sf::Event& _event) override;
        void OnPointerUnClick() override{}
#pragma endregion override
    };
}
