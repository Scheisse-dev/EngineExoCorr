#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include "../../Utils/Singleton/Singleton.h"

namespace Engine::UI
{
    class UIElement;
}

class IPointerClickHandler;

namespace Engine::Manager
{
    class EventSystem : public Utils::Singleton<EventSystem>
    {
        DECLARE_CLASS_INFO(EventSystem, Singleton<EventSystem>)
#pragma region f/p
    private:
        std::vector<UI::UIElement*> elements = std::vector<UI::UIElement*>();
        std::vector<UI::UIElement*> hoveredElements = std::vector<UI::UIElement*>();
        IPointerClickHandler* pointerClickHandler = nullptr;
#pragma endregion f/p
#pragma region constructor
    public:
        EventSystem() = default;
#pragma endregion constructor
#pragma region methods
    private:
        void RemoveHoveredElement(const UI::UIElement* _element);
        void CheckPointerClickHandler(const sf::Event& _event, Engine::UI::UIElement* _element);
        void CheckEnterHandler(Engine::UI::UIElement* _element);
        void CheckExitHandler(Engine::UI::UIElement* _element);
        void CheckPointerMoveHandler(const sf::Event& _event, Engine::UI::UIElement* _element);
        bool CheckTextEntered(const sf::Event& _event, Engine::UI::UIElement* _element);
    public:
        void Register(UI::UIElement* _element);
        void UnRegister(UI::UIElement* _element);
        void Update(const sf::Event& _event, const sf::Window* _window);
        void Draw(sf::RenderWindow* _window) const;
#pragma endregion methods
#pragma region override
    public:
        void OnDestroy() override;
#pragma endregion override
    };
}
