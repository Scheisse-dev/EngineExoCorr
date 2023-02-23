#pragma once
#include <SFML/Window/Event.hpp>

class ITextEntered
{
public:
    virtual ~ITextEntered() = default;
    virtual void OnTextEntered(sf::Uint32 _unicode) = 0;
};
