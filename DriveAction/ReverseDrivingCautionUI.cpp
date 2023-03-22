#include "ReverseDrivingCautionUI.h"
#include "UIDataStruct.h"
#include "Utility.h"
#include "SoundPlayer.h"
ReverseDrivingCautionUI::ReverseDrivingCautionUI()
{
    data.x = SCREEN_WIDTH / 2;
    data.y = UI_SCREEN_HEIGHT * -1.0f;
    data.dataHandle = LoadGraph(returnGraphAddress.c_str(), false);
    returnGraphUI = new ImgUI(graphSize,data);
    SoundPlayer::LoadSound(returnSoundAddress);
    time = limitedTime;
}

ReverseDrivingCautionUI::~ReverseDrivingCautionUI()
{
    SAFE_DELETE(returnGraphUI);
    DeleteGraph(data.dataHandle);
}

void ReverseDrivingCautionUI::Update(bool reverse, float deltaTime)
{
    if (reverse)
    {
        time -= deltaTime;
        if (time < 0 && !SoundPlayer::IsPlaySound(returnSoundAddress))
        {
            SoundPlayer::Play2DSE(returnSoundAddress);
            data.y -= deltaTime;
            returnGraphUI->SetXY(data.x,data.y);
        }
    }
    else
    {
        time = limitedTime;
        SoundPlayer::StopSound(returnSoundAddress);
    }
}

void ReverseDrivingCautionUI::Draw()
{
    if (time < 0)
    {
        returnGraphUI->DrawUI();
    }
}
