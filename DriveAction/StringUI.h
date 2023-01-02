#pragma once
#include "UIDataStruct.h"
#include "UI.h"
struct UIStringData;
class StringUI:public UI
{
public:
    StringUI();
    StringUI(unsigned int colorValue, UIData data);
    ~StringUI();
    void Draw();
private:
    UIData stringData;
    unsigned int color;
};

