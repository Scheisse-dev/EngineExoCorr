#pragma once

class IPointerMoveHandler
{
public:
    virtual ~IPointerMoveHandler() = default;
    virtual void OnPointerMove(float _x, float _y) = 0;
};