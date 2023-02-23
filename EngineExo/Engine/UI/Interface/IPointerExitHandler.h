#pragma once

class IPointerExitHandler
{
public:
    virtual ~IPointerExitHandler() = default;
    virtual void OnPointerExit() = 0;
};