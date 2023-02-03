#include "UIManager.h"
#include "DxLib.h"
#include "Car.h"
#include "Utility.h"

UIManager::UIManager()
{
}

UIManager::~UIManager()
{
    DeleteAllUI();
}

int UIManager::AddUI(UI* ui)
{
    uiVec.push_back(ui);
    return uiVec.size()-1;
}

void UIManager::Update(int index, std::string updateString)
{

}

void UIManager::Update(int index, int x, int y)
{
    uiVec[index]->SetXY(x, y);
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


