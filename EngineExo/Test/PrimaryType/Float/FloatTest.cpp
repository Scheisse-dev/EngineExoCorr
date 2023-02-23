#include "FloatTest.h"

#include "../../../Engine/PrimaryType/Float/Float.h"
#include "../../../Engine/PrimaryType/Boolean/Boolean.h"
#include "../../../Engine/Utils/DebugMacro.h"


void Test::FloatTest::Test()
{
    Engine::PrimaryType::Float _a = 10;
    Engine::PrimaryType::Float _b = 15;

    checkLow((_a < _b), "a is not < to b")
    checkLow((_b > _a), "b is not > to a")

    Engine::PrimaryType::Float _c = Engine::PrimaryType::Float::Parse("15");
    checkLow((_c == 15.0f), "c is not equals to 15")
    checkLow((_c != _a), "c is not != to a")
    checkLow((_b >= _c), "b is not >= to c")
    checkLow((_a <= _c), "a is not <= to c")

    Engine::PrimaryType::Float _d = _a + _b;
    checkLow((_d == 25.0f), "d is not equals to a + b = 25")
    _d = _b - _a;
    checkLow((_d == 5.0f), "d is not equals to b - a = 5")
    _d = _a * _b;
    checkLow((_d == 150.0f), "d is not equals to a * b = 150")
    _d = _a / 2.0f;
    checkLow((_d == 5.0f), "d is not equals to a / 2 = 5")
    _d += 250.0f;
    checkLow((_d == 255.0f), "d is not equals to d += 250 = 255")
    _d -= 30.0f;
    checkLow((_d == 225.0f), "d is not equals to d -= 30 = 225")
    _d *= 2.0f;
    checkLow((_d == 450.0f), "d is not equals to d *= 2 = 450")
    _d /= 4.0f;
    checkLow((_d == 112.5f), "d is not equals to d /= 4 = 112.5")

    _d = Engine::PrimaryType::Float::NaN;
    checkLow((Engine::PrimaryType::Float::IsNaN(_d)), "d is not equals to NaN")
    _d = Engine::PrimaryType::Float::Epsilon;
    checkLow((Engine::PrimaryType::Float::IsEpsilon(_d)), "d is not equals to Epsilon")
    _d = Engine::PrimaryType::Float::PositiveInfinity;
    checkLow((Engine::PrimaryType::Float::IsPositiveInfinity(_d)), "d is not equals to Positive Infinity")
    _d = Engine::PrimaryType::Float::NegativeInfinity;
    checkLow((Engine::PrimaryType::Float::IsNegativeInfinity(_d)), "d is not equals to Negative Infinity")
    
    Engine::Utils::Console::Log("[Float][Test] => successful !");
}
