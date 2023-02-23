#pragma once
#include "../../Event/Action/ActionInternal.h"
#include "../Element/UIElement.h"
#include "../Interface/IPointerClickHandler.h"
#include "../Interface/IPointerEnterHandler.h"
#include "../Interface/IPointerExitHandler.h"

namespace Engine::UI
{
    class AssetButton : public UIElement, public IPointerClickHandler, public IPointerEnterHandler, public IPointerExitHandler
    {
        DECLARE_CLASS_INFO(AssetButton, UIElement)
#pragma region f/p
    private:
        float width = 100.0f;
        float height = 40.0f;
        sf::Text text = sf::Text();
        sf::Color baseColor = sf::Color::White;
        sf::Color enterColor = sf::Color(189, 195, 199);
        Object* object = nullptr;
        Action<Object*> OnClick = nullptr;
#pragma endregion f/p
#pragma region constructor
    public:
        AssetButton() = default;
        AssetButton(const std::string& _text, float _width, float _height, Object* _object, const Action<Object*>& _onClick = nullptr);
#pragma endregion constructor
#pragma region methods
    public:
        template<typename Class>
        void AddListener(Class* _instance, void (Class::*ptr)(Object*))
        {
            OnClick.AddDynamic(_instance, ptr);
        }
        template<typename Class>
        void RemoveListener(Class* _instance, void (Class::*ptr)(Object*))
        {
            OnClick.RemoveDynamic(_instance, ptr);
        }
        void SetBackgroundColor(const sf::Color& _color);
#pragma endregion methods
#pragma region override
    public:
        void OnPointerEnter() override;
        void OnPointerExit() override;
        void OnPointerClick(const sf::Event& _event) override;
        void OnPointerUnClick() override {}
        void SetPosition(const PrimaryType::Vector2& _position) override;
        void Draw(sf::RenderWindow* _window) override;
#pragma endregion override
    };
}
