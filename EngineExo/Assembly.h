#pragma once
#include "Engine/Utils/ObjectMacro.h"

using namespace Engine;

#include "Engine\Component\Component.h"
REGISTER_TYPE(Component)
#include "Engine\GameObject\GameObject.h"
REGISTER_TYPE(GameObject)
#include "Engine\Object\Object.h"
REGISTER_TYPE(Object)
#include "Engine\Transform\Transform.h"
REGISTER_TYPE(Transform)
using namespace Engine::PrimaryType;

#include "Engine\PrimaryType\Boolean\Boolean.h"
REGISTER_TYPE(Boolean)
#include "Engine\PrimaryType\Integer\Integer.h"
REGISTER_TYPE(Integer)
#include "Engine\PrimaryType\String\String.h"
REGISTER_TYPE(String)
#include "Engine\PrimaryType\Vector\Vector2.h"
REGISTER_TYPE(Vector2)
using namespace Engine::Reflection;

#include "Engine\Reflection\Field\FieldInfo.h"
REGISTER_TYPE(FieldInfo)
using namespace Test;

#include "Test\Component\PlayerComponent.h"
REGISTER_TYPE(PlayerComponent)
#include "Test\PrimaryType\Integer\IntegerTest.h"
REGISTER_TYPE(IntegerTest)

