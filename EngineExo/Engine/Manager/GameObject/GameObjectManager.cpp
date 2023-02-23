#include "GameObjectManager.h"

#include "../../GameObject/GameObject.h"

Engine::Manager::GameObjectManager::GameObjectManager(const GameObjectManager& _copy)
{
    gameobjects = _copy.gameobjects;
}


void Engine::Manager::GameObjectManager::Register(GameObject* _object)
{
    gameobjects.push_back(_object);
}

void Engine::Manager::GameObjectManager::UnRegister(GameObject* _object)
{
    std::erase(gameobjects, _object);
}

void Engine::Manager::GameObjectManager::Update() const
{
    for (const GameObject* _gameobject : gameobjects)
    {
        for (Component* _component : _gameobject->Components())
        {
            if (_component->enabled)
            {
                Reflection::MethodInfo<void>* _method = _component->GetFunction<void>("Update");
                if (_method == nullptr) continue;
                _method->Invoke(_component);
            }
        }
    }
}
void Engine::Manager::GameObjectManager::Draw(const Window::EngineWindow* _window) const
{
    for (const GameObject* _object : gameobjects)
        _object->Draw(_window);
}

void Engine::Manager::GameObjectManager::OnDestroy()
{
    for (GameObject*& _object : gameobjects)
    {
        delete _object;
        _object = nullptr;
    }
    gameobjects.clear();
}
