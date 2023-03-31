#include "PostGoalStaging.h"
#include "Utility.h"
#include "SoundPlayer.h"
#include "UserInput.h"
#include "ResultScore.h"
PostGoalStaging::PostGoalStaging()
{
    SoundPlayer::StopAllSound();
    x = 0.0f;
    y = SCREEN_HEIGHT;
    y /= 2;
    UIData goalMarkerUI;
    goalMarkerUI.x = x;
    goalMarkerUI.y = y;
    goalMarkerUI.dataHandle = CreateFontToHandle("BIZ UDゴシック", 122, 3, DX_FONTTYPE_NORMAL);
    stringUI = new StringUI(goalMarkerUIColor, goalMarkerUI, "終了");
    switchUI = new SwitchUI();
    SoundPlayer::LoadSound(clapSE);
    SoundPlayer::Play2DSE(clapSE);

    UIData uidata = {};
    uidata.dataHandle = 
    uidata.y = UI_SCREEN_HEIGHT * 2;
    uidata.x = UI_SCREEN_WIDTH * 8;
    uidata.dataHandle = LoadGraph("data/TimeBonus.png");
    timeUI = uidata;
    uidata.y = UI_SCREEN_HEIGHT * 6;
    uidata.dataHandle = LoadGraph("data/Damage.png");
    hitUI = uidata;
    uidata.y = UI_SCREEN_HEIGHT * 10;
    uidata.dataHandle = LoadGraph("data/CoinBonus.png");
    coinUI = uidata;
    uidata.y = UI_SCREEN_HEIGHT * 15; 
    uidata.dataHandle = LoadGraph("data/Score.png");
    scoreUI = uidata;
    
    num = new NumUI();
    screenGraph = MakeGraph(SCREEN_WIDTH, SCREEN_HEIGHT);
    GetDrawScreenGraph(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, screenGraph);
}


PostGoalStaging::~PostGoalStaging()
{
    DeleteGraph(screenGraph);
    SAFE_DELETE(switchUI);
    SAFE_DELETE(stringUI);
}

bool PostGoalStaging::Update()
{
    
    if(!isEndGoalUI)
    {
        if (UserInput::GetInputState(Space) == Detach)
        {
            isEndGoalUI = true;
        }
        if (x > SCREEN_WIDTH)
        {
            isEndGoalUI = true;
           
        }
        else
        {
            x += goalMoveX;
            stringUI->SetXY(static_cast<int>(x), static_cast<int>(y));
        }
    }
    else
    {
        if (UserInput::GetInputState(Space) == Detach)
        {
            return true;
        }
        switchUI->Update();
    }
    return false;
}

void PostGoalStaging::Draw()
{
    SetDrawBright(60, 60, 60);
    DrawGraph(0, 0, screenGraph, false);
    SetDrawBright(255, 255, 255);
    if (isEndGoalUI)
    {
        switchUI->Draw();
        DrawRotaGraph(scoreUI.x, scoreUI.y, 1, 0, scoreUI.dataHandle, true);
        num->Draw(numDrawX, scoreUI.y, ResultScore::GetScore(), numSize);

        DrawRotaGraph(coinUI.x, coinUI.y, scoreSize, 0, coinUI.dataHandle, true);
        num->Draw(numDrawX, coinUI.y,ResultScore::GetCoinScore(), numSize);

        DrawRotaGraph(hitUI.x, hitUI.y, scoreSize, 0, hitUI.dataHandle, true);
        num->Draw(numDrawX, hitUI.y, ResultScore::GetHitScore(), numSize);

        DrawRotaGraph(timeUI.x, timeUI.y, scoreSize, 0, timeUI.dataHandle, true);
        num->Draw(numDrawX, timeUI.y, ResultScore::GetTimeScore(), numSize);
    }
    else
    {
        stringUI->DrawRightAlignedString();
    }
}
