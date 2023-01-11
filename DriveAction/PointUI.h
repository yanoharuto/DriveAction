#pragma once
#include "UI.h"
class PointUI :
    public UI
{
public:
    PointUI(unsigned int color, UIData uiData,float r);
    ~PointUI();
    void DrawUI() override;
private:
    unsigned int pointColor;
    float radius;
};