#pragma once
#include <vector>
#include "UI.h"
class Car;
class UIManager
{
public:
    UIManager();
    ~UIManager();
    int AddUI(UI* ui);
    void DrawUI();
    void DeleteArgumentUI(int uiNum);
    void DeleteAllUI();
private:
    std::vector<UI*> uiVec;
};
