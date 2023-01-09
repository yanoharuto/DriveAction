#pragma once
#include "UI.h"
class PointUI :
    public UI
{
public:
    PointUI(unsigned int color, UIData uiData);
    ~PointUI();
    void Update(std::string xy) override;
    void DrawUI() override;
private:
    UIData uiData;
};