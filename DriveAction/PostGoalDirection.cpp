#include "PostGoalDirection.h"
#include "StringUI.h"
#include "DxLib.h"
#include "Utility.h"
PostGoalDirection::PostGoalDirection()
{
}

PostGoalDirection::PostGoalDirection(UIManager* uimanager)
{
    x = 0.0f;
    y = SCREEN_HEIGHT;
    y /= 2;
    UIData goalMarkerUI;
    goalMarkerUI.x = x;
    goalMarkerUI.y = y;
    goalMarkerUI.dataHandle = CreateFontToHandle("BIZ UDゴシック",122,3,DX_FONTTYPE_NORMAL);
    StringUI* goalUI = new StringUI(goalMarkerUIColor,goalMarkerUI,"Goal!!!");
    goalMarkerUINum = uimanager->AddUI(goalUI);
}

PostGoalDirection::~PostGoalDirection()
{
}

bool PostGoalDirection::Update(float deltaTime, UIManager* uimanager)
{
    int key = GetJoypadInputState(DX_INPUT_KEY_PAD1);

    time += deltaTime;
    int width = SCREEN_WIDTH;
    if (key & PAD_INPUT_10)
    {
        return true;
    }
    if(!isEndGoalUI)
    {
        if (x > width)
        {
            isEndGoalUI = true;
            x = SCREEN_WIDTH;
            x /= 2;
            y = SCREEN_HEIGHT;
            y /= 5;
            y *= 3;
            UIData spaceKeyUI;
            spaceKeyUI.x = x - 50;
            spaceKeyUI.y = y;
            spaceKeyUI.dataHandle = CreateFontToHandle("BIZ UDゴシック", bigPleaseSpaceKeySize, 3, DX_FONTTYPE_NORMAL);
            StringUI* smallUI = new StringUI(pleaseSpaceKeyUIColor, spaceKeyUI, pleaseSpaceKeyUIString);
            smallPleaseSpaceKeyUINum = uimanager->AddUI(smallUI);


            x += bigPleaseSpaceKeySize - smallPleaseSpaceKeySize;
            spaceKeyUI.dataHandle = CreateFontToHandle("BIZ UDゴシック", smallPleaseSpaceKeySize, 3, DX_FONTTYPE_NORMAL);
            StringUI* bigUI = new StringUI(pleaseSpaceKeyUIColor, spaceKeyUI, pleaseSpaceKeyUIString);
            bigPleaseSpaceKeyUINum= uimanager->AddUI(bigUI);
            uimanager->StopArgumentDrawUI(bigPleaseSpaceKeyUINum,true);
        }
        else
        {
            x += goalMoveX * deltaTime;
            uimanager->Update(goalMarkerUINum, static_cast<int>(x), y);
        }
    }
    else
    {
        if ((int)time % 2 < 1)
        {
            uimanager->StopArgumentDrawUI(bigPleaseSpaceKeyUINum, true);
            uimanager->StopArgumentDrawUI(smallPleaseSpaceKeyUINum, false);
        }
        else
        {
            uimanager->StopArgumentDrawUI(bigPleaseSpaceKeyUINum, false);
            uimanager->StopArgumentDrawUI(smallPleaseSpaceKeyUINum, true);
        }
    }
    return false;
}
