#include "AssetWindow.h"

#include "../../AssetDataBase/AssetDataBase.h"
#include "../../Window/Engine/EngineWindow.h"
#include "../../PrimaryType/Vector/Vector2.h"
#include "../../Selection/Selection.h"
#include "../../UI/AssetButton/AssetButton.h"
#pragma region constructor
Engine::Editor::AssetWindow::AssetWindow() : super("Assets")
{
    shape = sf::RectangleShape(PrimaryType::Vector2(Window::EngineWindow::Instance()->Width(), 150));
    shape.setFillColor(sf::Color(50, 50, 50, 255));
    SetPosition(PrimaryType::Vector2(0, Window::EngineWindow::Instance()->Height() - 150));
}
Engine::Editor::AssetWindow::AssetWindow(const AssetWindow& _copy) = default;
#pragma endregion constructor
#pragma region methods
void Engine::Editor::AssetWindow::RefreshAssetGUI()
{
    std::vector<Object*> _assets = AssetDataBase::LoadAllAssets();
    PrimaryType::Vector2 _position = PrimaryType::Vector2(50, Window::EngineWindow::Instance()->Height() - 140);
    for (Object* _asset : _assets)
    {
        UI::AssetButton* _button = new UI::AssetButton("", 100, 50, _asset, nullptr);
        _button->AddListener(Selection::Instance(), &Selection::SetSelection);
        _button->SetPosition(_position);
        _position.x += 110;
    }
}
#pragma endregion methods
#pragma region override
void Engine::Editor::AssetWindow::Open()
{
    RefreshAssetGUI();
    super::Open();
}
#pragma endregion override
