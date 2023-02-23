#include "IntegerTest.h"

#include "../../../Engine/PrimaryType/Integer/Integer.h"
#include "../../../Engine/PrimaryType/Boolean/Boolean.h"
#include "../../../Engine/Utils/DebugMacro.h"
#pragma region methods

Test::IntegerTest::IntegerTest(const IntegerTest& _copy)
{
    
}


void Test::IntegerTest::Test()
{
    Engine::PrimaryType::Integer _a = 10;
    Engine::PrimaryType::Integer _b = 15;

    checkLow((_a < _b), "a is not < to b")
    checkLow((_b > _a), "b is not > to a")

    Engine::PrimaryType::Integer _c = Engine::PrimaryType::Integer::Parse("15");
    checkLow((_c == 15), "c is not equals to 15")
    checkLow((_c != _a), "c is not != to a")
    checkLow((_b >= _c), "b is not >= to c")
    checkLow((_a <= _c), "a is not <= to c")

    Engine::PrimaryType::Integer _d = _a + _b;
    checkLow((_d == 25), "d is not equals to a + b = 25")
    _d = _b - _a;
    checkLow((_d == 5), "d is not equals to b - a = 5")
    _d = _a * _b;
    checkLow((_d == 150), "d is not equals to a * b = 150")
    _d = _a / 2;
    checkLow((_d == 5), "d is not equals to a / 2 = 5")
    _d = _a % _b;
    checkLow((_d == 10), "d is not equals to a % b = 10")
    _d += 250;
    checkLow((_d == 260), "d is not equals to d += 250 = 260")
    _d -= 30;
    checkLow((_d == 230), "d is not equals to d -= 30 = 230")
    _d *= 2;
    checkLow((_d == 460), "d is not equals to d *= 2 = 460")
    _d /= 4;
    checkLow((_d == 115), "d is not equals to d /= 4 = 115")
    _d %= 2;
    checkLow((_d == 1), "d is not equals to d %= 2 = 1")
    ++_d;
    checkLow((_d == 2), "d is not equals to ++d = 2")
    --_d;
    checkLow((_d == 1), "d is not equals to --d = 1")
    
}
#pragma endregion methods
