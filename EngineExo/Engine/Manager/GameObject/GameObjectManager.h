#pragma once
#include "../../Utils/Singleton/Singleton.h"

namespace Engine
{
    class GameObject;
    namespace Window
    {
        class EngineWindow;
    }
}
namespace Engine::Manager
{
    class GameObjectManager : public Utils::Singleton<GameObjectManager>
    {
        DECLARE_CLASS_INFO(GameObjectManager, Singleton<GameObjectManager>)
#pragma region f/p
    private:
        std::vector<GameObject*> gameobjects = std::vector<GameObject*>();
#pragma region f/p
    public:
        GameObjectManager() = default;
#pragma region methods
    public:
        void Register(GameObject* _object);
        void UnRegister(GameObject* _object);
        void Update() const;
        void Draw(const Window::EngineWindow* _window) const;
        void OnDestroy() override;
#pragma endregion methods
    };
}
