#pragma once
#include <SFML/Window/Event.hpp>

class IPointerClickHandler
{
public:
    virtual ~IPointerClickHandler() = default;
    virtual void OnPointerClick(const sf::Event& _event) = 0;
    virtual void OnPointerUnClick() = 0;
};
