#pragma once
#include "../Object/Object.h"
#include "../UI/Element/UIElement.h"
#include "../PrimaryType/Vector/Vector2.h"

namespace Engine::Editor
{
    enum class EValueType
    {
        Int,
        Bool,
        Float,
        Double,
        String,
        List,
        Vector,
        Object
    };
    class Editor : public Object
    {
        DECLARE_CLASS_INFO(Editor, Object)
#pragma region f/p
    private:
        std::vector<UI::UIElement*> elements = std::vector<UI::UIElement*>();
        Object* currentObjectEdit = nullptr;
        PrimaryType::Vector2 currentPosition = PrimaryType::Vector2(0,0);
        PrimaryType::Vector2 initialPosition = PrimaryType::Vector2(0,0);
#pragma endregion f/p
#pragma region constructor/destructor
    public:
        Editor() = default;
        Editor(Object* _object);
        ~Editor() override;
#pragma endregion constructor/destructor
#pragma region methods
    private:
        static EValueType GetValueType(Object* _object);
        void CreateToggleProperty(Engine::Reflection::FieldInfo* _field);
        void DisplayProperties(const PrimaryType::String& _name, std::vector<Engine::Reflection::FieldInfo*> _allFields);
    public:
        void SetObjectEdit(Object* _object);
        void SetPosition(const PrimaryType::Vector2& _position);
        virtual void InspectorGUI();
        Object* ObjectEdit();
        std::vector<UI::UIElement*> Elements() const;
#pragma endregion methods
    };
}
