#pragma once
#include <source_location>

#include "../Object/Object.h"
#include "../PrimaryType/String/String.h"

namespace Engine
{
    class Exception : public Object
    {
        DECLARE_CLASS_INFO(Exception, Object)
#pragma region f/p
    private:
        PrimaryType::String message = "";
#pragma endregion f/p
#pragma region constructor
    public:
        Exception(const std::source_location& _source = std::source_location::current());
        Exception(const char* _error, const std::source_location& _source = std::source_location::current());
#pragma endregion constructor
#pragma region methods
    public:
        PrimaryType::String Error() const;
#pragma endregion methods
#pragma region override
    public:
        PrimaryType::String ToString() const override;
#pragma endregion override
    };
}