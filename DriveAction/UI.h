#pragma once
#include "UIDataStruct.h"
#include <string>
class UI
{
public:
    UI() { uiData = {}; };
    UI(UIData data) { uiData = data; };
    virtual ~UI() {};
    virtual void DrawUI() {};
    virtual void Update(std::string updateString) {};
    void Update(int x, int y) { uiData.x = x; uiData.y = y; };
    void StopDrawUI(bool boolvalue) { IsStopDrawUI = boolvalue; };
protected:
    UIData uiData;
    bool IsStopDrawUI=false;
};