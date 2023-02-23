#pragma once
#include "../ValueType/ValueType.h"
#include "../../Reflection/Function/Parameter/ParameterInfo.h"

namespace Engine::PrimaryType
{
    class Boolean;

    UCLASS()
    class String : public ValueType
    {
        DECLARE_CLASS_INFO(String, ValueType)
#pragma region f/p
    private:
        const char* value = nullptr;
        size_t length = 0;
#pragma endregion f/p
#pragma region constructor
    public:
        String() = default;
        String(const char* _value);
#pragma endregion constructor
#pragma region methods
    public:
        Boolean StartWith(char _c) const;
        Boolean EndWith(char _c) const;
        Boolean StartWith(const String& _str) const;
        Boolean EndWith(const String& _str) const;
        Boolean EqualsIgnoreCase(const String& _str) const;
        Boolean Contains(const String& _str) const;
        UFUNCTION() static Boolean IsNullOrEmpty(const String& _str);
REGISTER_METHOD(IsNullOrEmpty, &String::IsNullOrEmpty, (std::vector<Engine::Reflection::ParameterInfo*>{new Engine::Reflection::ParameterInfo("_str", 0)}), BindingFlags::Public | BindingFlags::Static)
        String SubString(size_t _begin) const;
        String SubString(size_t _begin, size_t _end) const;
        String Replace(const String& _old, const String& _new) const;
        String Replace(char _old, char _new) const;
        String Trim() const;
        String ToLower() const;
        String ToUpper() const;
        size_t FindFirstOf(char _c) const;
        size_t FindLastOf(char _c) const;
        size_t Length() const;
        void Append(const char* _str);
        void Append(char _c);
        void Append(const String& _str);
        const char* ToCstr() const;
#pragma endregion methods
#pragma region override
    public:
        String ToString() const override;
        void SerializeField(std::ostream& _os, const PrimaryType::String& _fieldName, int _index) override;
        void DeSerializeField(std::istream& _is, const PrimaryType::String& _fieldName) override;
#pragma endregion override
#pragma region operator
    public:
        String& operator+=(const char* _str);
        String& operator+=(const String& _str);
        String& operator+=(char _c);
        String& operator=(const String& _other);
        Object& operator=(const Object* _other);
        operator const char*();
        operator const char*() const;
        Boolean operator==(const String& _str) const;
        Boolean operator!=(const String& _str) const;
        Boolean operator==(const char* _str) const;
        Boolean operator!=(const char* _str) const;
#pragma endregion operator
    };
}
