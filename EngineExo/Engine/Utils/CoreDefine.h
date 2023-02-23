#pragma once
#include "../PrimaryType/String/String.h"
#include "Template/Template.h"

#define INDEX_NONE -1

template<typename T>
Engine::PrimaryType::String ToString(T item)
{
    if constexpr (std::is_base_of_v<Engine::Object, T>)
    {
        return item.ToString();
    }
    else
    {
        return std::to_string(item).c_str();
    }
}

template<typename T>
Engine::PrimaryType::String ToString(T* item)
{
    return item->ToString();
}
