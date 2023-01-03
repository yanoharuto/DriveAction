#include "UIManager.h"
#include "DxLib.h"
#include "Car.h"
#include "Utility.h"

UIManager::UIManager()
{
}

UIManager::~UIManager()
{
}

int UIManager::AddUI(UI* ui)
{
    uiVec.push_back(ui);
    return uiVec.size();
}

void UIManager::DrawUI()
{
    for (int i = 0; i < uiVec.size(); i++)
    {
        uiVec[i]->DrawUI();
    }
}


void UIManager::DeleteArgumentUI(int uiNum)
{
    SAFE_DELETE(uiVec[uiNum]);
    uiVec.erase(uiVec.begin() + uiNum);
}

void UIManager::DeleteAllUI()
{
    for (int i = 0; i < uiVec.size(); i++)
    {
        DeleteArgumentUI(i);
    }
}