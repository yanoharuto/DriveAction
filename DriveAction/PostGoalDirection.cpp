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
    goalMarkerUI.dataHandle = CreateFontToHandle("BIZ UDƒSƒVƒbƒN",122,3,DX_FONTTYPE_NORMAL);
    StringUI* goalUI = new StringUI(GetColor(goalFontRed,goalFontGreen,goalFontBlue),goalMarkerUI,"Goal!!!");
    goalMarkerNum = uimanager->AddUI(goalUI);
}

PostGoalDirection::~PostGoalDirection()
{
}

bool PostGoalDirection::Update(float deltaTime, UIManager* uimanager)
{
    int key = GetJoypadInputState(DX_INPUT_KEY_PAD1);

    uimanager->Update(goalMarkerNum, static_cast<int>(x), y);
    int width = SCREEN_WIDTH;
    if (x > width)
    {

        if (key & PAD_INPUT_10)
        {
            return true;
        }
    }
    else
    {
        x += goalMoveX * deltaTime;
    }
    return false;
}
