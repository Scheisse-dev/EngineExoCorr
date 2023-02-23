#pragma once

class IPointerEnterHandler
{
public:
    virtual ~IPointerEnterHandler() = default;
    virtual void OnPointerEnter() = 0;
};