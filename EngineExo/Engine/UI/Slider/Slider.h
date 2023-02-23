#pragma once
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "../../Event/Action/ActionInternal.h"
#include "../Element/UIElement.h"
#include "../Interface/IPointerMoveHandler.h"

namespace Engine::UI
{
    class Slider : public UIElement, public IPointerMoveHandler
    {
        DECLARE_CLASS_INFO(Slider, UIElement)
#pragma region f/p
    private:
        sf::CircleShape* handle = nullptr;
        sf::RectangleShape* box = nullptr;
        float minValue = 0.0f;
        float maxValue = 100.0f;
        float currentValue = 0.0f;
    public:
        Action<float> OnValueChanged = nullptr;
#pragma endregion f/p
#pragma region constructor/desutrctor
    public:
        Slider();
        Slider(float _min, float _max, float _value);
        Slider(float _value);
        ~Slider() override;
#pragma endregion constructor/destructor
#pragma region methods
    private:
        void UpdateHandlePosition() const;
    public:
        void SetValue(float _value);
        void SetMin(float _min);
        void SetMax(float _max);
#pragma endregion methods
#pragma region override
    public:
        void Draw(sf::RenderWindow* _window) override;
        void SetPosition(const PrimaryType::Vector2& _position) override;
        void OnPointerMove(float _x, float _y) override;
#pragma endregion override
    };
}
