#pragma once
#include "StaticObject.h"
/// <summary>
/// ÉRÅ[ÉX
/// </summary>
class CircuitTrack :
    public StaticObject
{
public:
    CircuitTrack();
    ~CircuitTrack();
    void Draw() override;

private:
    float const scaleValue = 0.15f;
};

