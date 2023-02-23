#pragma once
#include "../ValueType/ValueType.h"

namespace Engine::PrimaryType
{
    UCLASS()
    class Boolean : public ValueType
    {
        DECLARE_CLASS_INFO(Boolean, ValueType)
#pragma region f/p
    private:
        bool value = false;
#pragma endregion f/p
#pragma region constructor
    public:
        Boolean() = default;
        Boolean(bool _value);
#pragma endregion constructor
#pragma region override
    public:
        String ToString() const override;
        void SerializeField(std::ostream& _os, const PrimaryType::String& _fieldName, int _index) override;
        void DeSerializeField(std::istream& _is, const PrimaryType::String& _fieldName) override;
#pragma endregion override
#pragma region operator
    public:
        Boolean& operator=(const Boolean& _other);
        Boolean operator!() const;
        operator bool();
        operator bool() const;

#pragma endregion operator
    };
}
