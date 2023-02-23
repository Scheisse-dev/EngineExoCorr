#include "InspectorWindow.h"

#include "../../AssetDataBase/AssetDataBase.h"
#include "../../Window/Engine/EngineWindow.h"
#include "../../PrimaryType/Vector/Vector2.h"
#include "../../Selection/Selection.h"
#pragma region constructor
Engine::Editor::InspectorWindow::InspectorWindow() : super("Inspectors")
{
    const int _width = Window::EngineWindow::Instance()->Width();
    const int _height = Window::EngineWindow::Instance()->Height();
    shape = sf::RectangleShape(PrimaryType::Vector2(300, _height));
    shape.setFillColor(sf::Color(50,50,50,255));
    const PrimaryType::Vector2& _position = PrimaryType::Vector2(_width - 300, 25);
    SetPosition(_position);
    editor = new Editor(nullptr);
    editor->SetPosition(_position + PrimaryType::Vector2(15, 0));
    Selection::OnSelectionChanged.AddDynamic(this, &InspectorWindow::OnSelectionChanged);
}

Engine::Editor::InspectorWindow::~InspectorWindow()
{
    Selection::OnSelectionChanged.RemoveDynamic(this, &InspectorWindow::OnSelectionChanged);
    delete editor;
    editor = nullptr;
}

Engine::Editor::InspectorWindow::InspectorWindow(const InspectorWindow& _copy) = default;
#pragma endregion constructor
#pragma region methods
void Engine::Editor::InspectorWindow::OnSelectionChanged(Object* _o)
{
    if (editor->ObjectEdit() != nullptr)
    {
        const std::string& _path = AssetDataBase::GetAssetPath(editor->ObjectEdit());
        std::ofstream _of(_path);
        editor->ObjectEdit()->Serialize(_of);
    }
    editor->SetObjectEdit(_o);
    editor->InspectorGUI();
}
#pragma endregion methods