#include "ReverseDrivingCautionUI.h"
#include "UIDataStruct.h"
#include "Utility.h"
ReverseDrivingCautionUI::ReverseDrivingCautionUI()
{
    data.x = SCREEN_WIDTH / 2;
    data.y = SCREEN_HEIGHT / 7;
    data.dataHandle = LoadGraph(returnGraphAddress.c_str(), false);
    returnGraphUI = new ImgUI(graphSize,data);

    time = limitedTime;
}

ReverseDrivingCautionUI::~ReverseDrivingCautionUI()
{
    SAFE_DELETE(returnGraphUI);
    DeleteGraph(data.dataHandle);
}

void ReverseDrivingCautionUI::Update(VECTOR carDir, VECTOR checkPointDir, float deltaTime)
{
    float dot = VDot(carDir, checkPointDir);
    if (dot <= -0.5)
    {
        time -= deltaTime;
    }
    else
    {
        time = limitedTime;
    }
    printfDx("%f\n", dot);
}

void ReverseDrivingCautionUI::Draw()
{
    if (time < 0)
    {
        returnGraphUI->DrawUI();
    }
}
