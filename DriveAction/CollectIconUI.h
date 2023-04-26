#pragma once
#include "UIManager.h"
class Timer;
struct UIData;
class CollectIconUI
{
public:
    CollectIconUI();
    CollectIconUI(int x,int y,float span);
    ~CollectIconUI();
    void Update();
    void Draw();
private:
    UIData iconData;
    Timer* timer;
};