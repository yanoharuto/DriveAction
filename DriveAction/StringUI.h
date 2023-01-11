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
    ~StringUI();
    void DrawUI()override;
    void Update(std::string updateString) override;
private:
    unsigned int color;
    std::string string;

};

