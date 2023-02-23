#include "Transform.h"

Engine::Transform::Transform(const Transform& _copy) : super(_copy)
{
    position = _copy.position;
}


Engine::Transform& Engine::Transform::operator=(const Transform& _other)
{
    position = _other.position;
    return *this;
}

Engine::Object& Engine::Transform::operator=(const Object* _obj)
{
    const Transform* _other = dynamic_cast<const Transform*>(_obj);
    if (_other == nullptr) return *this;
    super::operator=(_other);
    position = _other->position;
    return *this;
}
