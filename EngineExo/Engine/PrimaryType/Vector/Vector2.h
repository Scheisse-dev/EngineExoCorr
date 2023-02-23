#pragma once
#include <SFML/System/Vector2.hpp>

#include "../../PrimaryType/ValueType/ValueType.h"
#include "../Float/Float.h"

namespace Engine::PrimaryType
{
    UCLASS()
    class Vector2 : public ValueType
    {
        DECLARE_CLASS_INFO(Vector2, ValueType)
#pragma region f/p
    public:
        UPROPERTY() Float x = 0.0f;
REGISTER_FIELD(x, &x, BindingFlags::Public)
        UPROPERTY() Float y = 0.0f;
REGISTER_FIELD(y, &y, BindingFlags::Public)
#pragma endregion f/p
#pragma region constructor
    public:
        Vector2() = default;
        Vector2(const sf::Vector2f& _value);
        Vector2(float _x, float _y);
#pragma endregion constructor
#pragma region methods
    public:
        static Engine::PrimaryType::Vector2 MoveTowards(const Vector2& _current, const Vector2& _target, float _dt);
#pragma endregion methods
#pragma region override
    public:
        String ToString() const override;
        void SerializeField(std::ostream& _os, const PrimaryType::String& _fieldName, int _index) override;
        void DeSerializeField(std::istream& _is, const PrimaryType::String& _fieldName) override;
#pragma endregion override
#pragma region operator
    public:
        operator sf::Vector2f() const;
        Object& operator=(const Object* _obj) override;
        Vector2& operator=(const Vector2& _other);
        Vector2& operator+=(const Vector2& _other);
        Vector2& operator-=(const Vector2& _other);
        Vector2& operator*=(const Vector2& _other);
        Vector2& operator/=(const Vector2& _other);
        Vector2 operator+(const Vector2& _other) const;
        Vector2 operator-(const Vector2& _other) const;
        Vector2 operator*(const Vector2& _other) const;
        Vector2 operator/(const Vector2& _other) const;
        Boolean operator==(const Vector2& _other) const;
        Boolean operator!=(const Vector2& _other) const;
        Float& operator[](size_t _index);
        Float operator[](size_t _index) const;
#pragma endregion operator
    };
}
