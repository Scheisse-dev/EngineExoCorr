#pragma once
#include "../Window/EditorWindow.h"

namespace Engine::Editor
{
    class AssetWindow : public EditorWindow
    {
        DECLARE_CLASS_INFO(AssetWindow, EditorWindow)
#pragma region constructor
    public:
        AssetWindow();
#pragma endregion constructor
#pragma region methods
    public:
        void RefreshAssetGUI();
#pragma endregion methods
#pragma region override
    public:
        void Open() override;
#pragma endregion override
    };
}
