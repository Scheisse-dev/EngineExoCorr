#pragma once

namespace Engine::PrimaryType
{
    class Integer;
    
    class IList
    {
    public:
        virtual ~IList() = default;
        virtual size_t Count() const = 0;
        virtual Object* operator[](int _index) = 0;
    };
}
