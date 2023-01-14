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
    StringUI* goalUI = new StringUI(goalMarkerUIColor,goalMarkerUI,"Goal!!!");
    goalMarkerUINum = uimanager->AddUI(goalUI);

    switchUI = new SwitchUI();
}

PostGoalDirection::~PostGoalDirection()
{
    SAFE_DELETE(switchUI);
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
           
        }
        else
        {
            x += goalMoveX * deltaTime;
            uimanager->Update(goalMarkerUINum, static_cast<int>(x), y);
        }
    }
    else
    {
        switchUI->Update(deltaTime);
    }
    return false;
}

void PostGoalDirection::Draw()
{
    if (isEndGoalUI)
    {
        switchUI->Draw();
    }
}
