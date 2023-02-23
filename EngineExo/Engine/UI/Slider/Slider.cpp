#include "Slider.h"

#include "../../Manager/EventSystem/EventSystem.h"
#include "../../PrimaryType/Vector/Vector2.h"
#pragma region constructor/destructor
Engine::UI::Slider::Slider() : super()
{
    shape = new sf::RectangleShape(sf::Vector2f(150, 20));
    shape->setFillColor(sf::Color::Transparent);
    box = new sf::RectangleShape(sf::Vector2f(110, 4));
    box->setOrigin(shape->getOrigin());
    handle = new sf::CircleShape(8);
    handle->setOrigin(shape->getOrigin());
    SetValue(maxValue - minValue);
}

Engine::UI::Slider::Slider(float _min, float _max, float _value) : self()
{
    minValue = _min;
    maxValue = _max;
    currentValue = _value;
    SetValue(_value);
}
Engine::UI::Slider::Slider(float _value) : self(0.0f, 100.0f, _value)
{
}

Engine::UI::Slider::Slider(const Slider& _copy) : super(_copy)
{
    handle = _copy.handle;
    box = _copy.box;
    minValue = _copy.minValue;
    maxValue = _copy.maxValue;
    currentValue = _copy.currentValue;
    OnValueChanged = _copy.OnValueChanged;
}

Engine::UI::Slider::~Slider()
{
    if (handle)
    {
        delete handle;
        handle = nullptr;
    }
    if (box)
    {
        delete box;
        box = nullptr;
    }
}
#pragma endregion constructor/destructor
#pragma region methods
void Engine::UI::Slider::UpdateHandlePosition() const
{
    const float _diff = maxValue - minValue;
    const float _diffNewValue = currentValue - minValue;
    const float _boxSizeDiff = box->getSize().x / _diff;
    const float _x = (_boxSizeDiff * _diffNewValue) + shape->getPosition().x;
    handle->setPosition(sf::Vector2f(_x, handle->getPosition().y));
}
void Engine::UI::Slider::SetValue(float _value)
{
    currentValue = _value < minValue ? minValue : _value > maxValue ? maxValue : _value;
    OnValueChanged.Invoke(currentValue);
    UpdateHandlePosition();
}
void Engine::UI::Slider::SetMin(float _min)
{
    minValue = _min;
}
void Engine::UI::Slider::SetMax(float _max)
{
    maxValue = _max;
}
#pragma endregion methods
#pragma region override
void Engine::UI::Slider::Draw(sf::RenderWindow* _window)
{
    if (handle == nullptr || box == nullptr) return;
    super::Draw(_window);
    _window->draw(*box);
    _window->draw(*handle);
}
void Engine::UI::Slider::SetPosition(const PrimaryType::Vector2& _position)
{
    super::SetPosition(_position);
    box->setPosition(_position);
    handle->setPosition(_position - sf::Vector2f(0, 5));
}
void Engine::UI::Slider::OnPointerMove(float _x, float _y)
{
    const float _newValue = minValue + (_x - shape->getPosition().x) / box->getSize().x * (maxValue - minValue);
    SetValue(_newValue);
}
#pragma endregion override