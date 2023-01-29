#include "PostGoalDirection.h"
#include "Utility.h"
PostGoalDirection::PostGoalDirection()
{
    x = 0.0f;
    y = SCREEN_HEIGHT;
    y /= 2;
    UIData goalMarkerUI;
    goalMarkerUI.x = x;
    goalMarkerUI.y = y;
    goalMarkerUI.dataHandle = CreateFontToHandle("BIZ UDƒSƒVƒbƒN", 122, 3, DX_FONTTYPE_NORMAL);
    stringUI = new StringUI(goalMarkerUIColor, goalMarkerUI, "Goal!!!");
    switchUI = new SwitchUI();
}


PostGoalDirection::~PostGoalDirection()
{
    SAFE_DELETE(switchUI);
    SAFE_DELETE(stringUI);
}

bool PostGoalDirection::Update(float deltaTime)
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
            stringUI->SetXY(static_cast<int>(x), static_cast<int>(y));
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
    else
    {
        stringUI->DrawRightAlignedString();
    }
}
