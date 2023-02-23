#include <filesystem>
#include <iostream>
#include "Engine/Window/Engine/EngineWindow.h"
#include "Assembly.h"
#include "Engine/AssetDataBase/AssetDataBase.h"
#include "Engine/Editor/Asset/AssetWindow.h"
#include "Engine/Editor/Inspector/InspectorWindow.h"
#include "Engine/Manager/FontManager.h"
#include "Engine/Manager/GameObject/GameObjectManager.h"
#include "Engine/Manager/Texture/TextureManager.h"

int main()
{
    Manager::FontManager::Instance()->Init();
    Manager::TextureManager::Instance()->Init();
    Editor::AssetWindow* _assetWindow = new Editor::AssetWindow();
    _assetWindow->Open();
    Editor::InspectorWindow* _inspectorWindow = new Editor::InspectorWindow();
    _inspectorWindow->Open();
    Window::EngineWindow::Instance()->Open();
    
    Manager::GameObjectManager::Instance()->Destroy();
    Manager::FontManager::Instance()->Destroy();
    Manager::TextureManager::Instance()->Destroy();
    delete _assetWindow;
    delete _inspectorWindow;
    return 0;
}
