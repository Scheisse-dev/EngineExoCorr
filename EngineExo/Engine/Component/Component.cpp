#include "Component.h"
#include "../Utils/DebugMacro.h"

Engine::Component::Component(const Component& _copy)
{
    enabled = _copy.enabled;
    gameobject = _copy.gameobject;
}


#pragma region operator
Engine::Object& Engine::Component::operator=(const Object* _obj)
{
    const Component* _other = dynamic_cast<const Component*>(_obj);
    check((_other != nullptr), "[Component] operator= _obj is not Component", *this)
    super::operator=(_obj);
    enabled = _other->enabled;
    gameobject = _other->gameobject;
    return *this;
}
#pragma endregion operator
