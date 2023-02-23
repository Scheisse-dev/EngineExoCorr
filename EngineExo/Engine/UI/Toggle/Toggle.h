#pragma once
#include "../../Event/Action/ActionInternal.h"
#include "../Element/UIElement.h"
#include "../Interface/IPointerClickHandler.h"

#define TOGGLE_VALID_NAME "toggle_valid"
#define TOGGLE_INVALID_NAME "toggle_invalid"

namespace Engine::UI
{
    class Toggle : public UIElement, public IPointerClickHandler
    {
        DECLARE_CLASS_INFO(Toggle, UIElement)
#pragma region f/p
    private:
        bool status = false;
        sf::Texture* toggleFalseTexture = nullptr;
        sf::Texture* toggleTrueTexture = nullptr;
    public:
        Action<bool> OnValueChanged = nullptr;
        Action<Object*> OnValueChangedReflection = nullptr;
#pragma endregion f/p
#pragma region constructor
    public:
        Toggle();
        Toggle(bool _status);
#pragma endregion constructor
#pragma region methods
    public:
        void SetStatus(bool _status);
        void OnPointerClick(const sf::Event& _event) override;
        void OnPointerUnClick() override{}
#pragma endregion methods
    };
}
