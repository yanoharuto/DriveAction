#include "PointUI.h"
#include "DxLib.h"
PointUI::PointUI(unsigned int color, UIData uiData,float r)
    :UI(uiData)
{
    pointColor = color;
    radius = r;
}

PointUI::~PointUI()
{
}

void PointUI::DrawUI()
{
    if (!IsStopDrawUI)
    {
        DrawCircle(uiData.x, uiData.y, radius, pointColor, true);
    }
}