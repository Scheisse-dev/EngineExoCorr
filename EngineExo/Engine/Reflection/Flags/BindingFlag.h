#pragma once
#include "../../PrimaryType/Enum/Enum.h"

ENUM(BindingFlags, Public = 1, NoPublic = 2, Static = 4, Array = 8)

inline BindingFlags operator|(BindingFlags _lhs, BindingFlags _rhs)
{
    return BindingFlags((int)_lhs | (int)_rhs);
}

inline bool operator&(BindingFlags _lhs, int _rhs)
{
    return (int)_lhs & _rhs;
}

inline bool operator&(BindingFlags _lhs, BindingFlags _rhs)
{
    return (int)_lhs & (int)_rhs;
}