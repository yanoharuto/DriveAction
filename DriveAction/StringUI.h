#pragma once
#include <string>
#include "UIDataStruct.h"
#include "UI.h"
struct UIStringData;
class StringUI:public UI
{
public:
    StringUI();
    StringUI(unsigned int colorValue, UIData data);
    StringUI(unsigned int colorValue, UIData data, std::string str);
    ~StringUI();
    void DrawRightAlignedString();
    void DrawLeftAlignedString();
    void UpdateString(std::string updateString);
private:
    unsigned int color;
    std::string string;

};

