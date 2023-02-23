#include "Editor.h"

#include "../AssetDataBase/AssetDataBase.h"
#include "../Manager/EventSystem/EventSystem.h"
#include "../PrimaryType/Boolean/Boolean.h"
#include "../PrimaryType/Integer/Integer.h"
#include "../PrimaryType/String/String.h"
#include "../PrimaryType/Double/Double.h"
#include "../PrimaryType/List/IList.h"
#include "../Reflection/Field/FieldInfo.h"
#include "../UI/Label/Label.h"
#include "../UI/Slider/Slider.h"
#include "../UI/TextField/TextField.h"
#include "../UI/Toggle/Toggle.h"
#pragma region constructor
Engine::Editor::Editor::Editor(Object* _object) : super()
{
    currentObjectEdit = _object;
}
Engine::Editor::Editor::~Editor()
{
    if (currentObjectEdit != nullptr)
    {
        const std::string& _path = AssetDataBase::GetAssetPath(currentObjectEdit);
        std::ofstream _of(_path);
        currentObjectEdit->Serialize(_of);
    }
}
Engine::Editor::Editor::Editor(const Editor& _copy) : super(_copy)
{
    currentObjectEdit = _copy.currentObjectEdit;
}
#pragma endregion constructor
#pragma region methods
Engine::Editor::EValueType Engine::Editor::Editor::GetValueType(Object* _object)
{
    if (dynamic_cast<PrimaryType::Integer*>(_object)) return EValueType::Int;
    if (dynamic_cast<PrimaryType::String*>(_object)) return EValueType::String;
    if (dynamic_cast<PrimaryType::Float*>(_object)) return EValueType::Float;
    if (dynamic_cast<PrimaryType::Double*>(_object)) return EValueType::Double;
    if (dynamic_cast<PrimaryType::Boolean*>(_object)) return EValueType::Bool;
    if (dynamic_cast<PrimaryType::Vector2*>(_object)) return EValueType::Vector;
    if (dynamic_cast<PrimaryType::IList*>(_object)) return EValueType::List;
    return EValueType::Object;    
}

void Engine::Editor::Editor::SetObjectEdit(Object* _object)
{
    for (UI::UIElement* _element : elements)
    {
        Manager::EventSystem::Instance()->UnRegister(_element);
        delete _element;
    }
    elements.clear();
    currentPosition = initialPosition;
    currentObjectEdit = _object;
}
void Engine::Editor::Editor::SetPosition(const PrimaryType::Vector2& _position)
{
    currentPosition = _position;
    initialPosition = _position;
}

void Engine::Editor::Editor::CreateToggleProperty(Reflection::FieldInfo* _field)
{
    PrimaryType::Boolean* _value = dynamic_cast<PrimaryType::Boolean*>(_field->ReflectedObject());
    UI::Toggle* _toggle = new UI::Toggle(*_value);
    _toggle->OnValueChangedReflection.AddDynamic(_field->ReflectedObject(), &Object::SetValue<PrimaryType::Boolean>);
    _toggle->SetPosition(currentPosition);
    elements.push_back(_toggle);
    currentPosition.y += _toggle->Shape()->getGlobalBounds().height;
}

void Engine::Editor::Editor::DisplayProperties(const PrimaryType::String& _name, const std::vector<Engine::Reflection::FieldInfo*> _allFields)
{
    UI::Label* _label = new UI::Label(_name);
    _label->SetPosition(currentPosition);
    currentPosition.y += _label->Height() * 2;
    
    for (Reflection::FieldInfo* _field : _allFields)
    {
        switch (GetValueType(_field->ReflectedObject()))
        {
        case EValueType::Int: break;
        case EValueType::Bool:
            {
                CreateToggleProperty(_field);
                break;
            }
        case EValueType::Float: break;
        case EValueType::Double: break;
        case EValueType::String:
            {
                PrimaryType::String* _value = dynamic_cast<PrimaryType::String*>(_field->ReflectedObject());
                UI::TextField* _textField = new UI::TextField(_value->ToString(), PrimaryType::Vector2(200, 20));
                _textField->OnValueChangedReflection.AddDynamic(_field->ReflectedObject(), &Object::SetValue<PrimaryType::String>);
                _textField->SetPosition(currentPosition);
                currentPosition.y += _textField->Shape()->getGlobalBounds().height;
                elements.push_back(_textField);
                break;
            }
        case EValueType::List:
            {
                PrimaryType::IList* _list = dynamic_cast<PrimaryType::IList*>(_field->ReflectedObject());
                for (int i = 0; i < _list->Count(); i++)
                {
                    Object* _o = _list->operator[](i);
                    std::vector<Reflection::FieldInfo*> _otherFields = _o->Fields();
                    DisplayProperties(_o->ClassName(), _otherFields);
                }
                break;
            }
        case EValueType::Vector: break;
        case EValueType::Object: break;
        }
    }
}
void Engine::Editor::Editor::InspectorGUI()
{
    if (currentObjectEdit == nullptr) return;
    currentPosition.y += 30;
    const std::vector<Reflection::FieldInfo*> _allFields = currentObjectEdit->Fields();
    DisplayProperties(currentObjectEdit->ClassName(), _allFields);
}
Engine::Object* Engine::Editor::Editor::ObjectEdit()
{
    return currentObjectEdit;
}
std::vector<Engine::UI::UIElement*> Engine::Editor::Editor::Elements() const
{
    return elements;
}
#pragma endregion methods