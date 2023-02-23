#pragma once

template<typename T> struct IsPointer { enum { Value = false};};
template<typename T> struct IsPointer<T*> { enum { Value = true };};
template<typename T> struct IsPointer<const T> { enum {Value = IsPointer<T>::Value };};

template<typename Base, typename T>
constexpr bool IsSame(T)
{
    return std::is_same_v<Base, T>;
}

template<typename Base, typename Derived>
constexpr bool IsSame(Derived* _der)
{
    Base* _cast = (Base*)_der;
    return _cast != nullptr;
}