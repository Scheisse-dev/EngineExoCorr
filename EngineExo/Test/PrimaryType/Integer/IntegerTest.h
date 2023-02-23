#pragma once
#include "../../../Engine/Object/Object.h"

namespace Test
{
    UCLASS()
    class IntegerTest : public Engine::Object
    {
        DECLARE_CLASS_INFO(IntegerTest, Object)
    public:
        static void Test();
        IntegerTest() = default;
    };
}
