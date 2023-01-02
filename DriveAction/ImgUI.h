#pragma once
#include "UI.h"
#include "UIDataStruct.h"
class ImgUI:public UI
{
public:
    ImgUI();
    ImgUI(UIData data);
    ~ImgUI();
    void DrawUI() override;
private:
    UIData imgData;
};

