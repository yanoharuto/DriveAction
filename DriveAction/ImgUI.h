#pragma once
#include "UI.h"
#include "UIDataStruct.h"
class ImgUI:public UI
{
public:
    ImgUI();
    ImgUI(float size,UIData data);
    ~ImgUI();
    void DrawUI() override;
private:
    float rate;
};

