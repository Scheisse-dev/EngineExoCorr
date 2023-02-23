#pragma once
#include "../Event/Action/ActionInternal.h"
#include "../Object/Object.h"
#include "../Utils/Singleton/Singleton.h"

namespace Engine
{
    class Selection : public Utils::Singleton<Selection>
    {
        DECLARE_CLASS_INFO(Selection, Singleton<Selection>)
#pragma region f/p
    private:
        Object* selected = nullptr;
    public:
        static inline Action<Object*> OnSelectionChanged = nullptr;
#pragma endregion f/p
#pragma region constructor
    public:
        Selection() = default;
#pragma endregion constructor
#pragma region methods
    public:
        void SetSelection(Object* _obj);
        Object* GetSelected();
#pragma endregion methods
    };
}
