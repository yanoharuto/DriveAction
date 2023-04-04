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
    SoundPlayer::LoadSound(rouretteSE);
    SoundPlayer::LoadSound(stopSE);
    SoundPlayer::Play2DSE(clapSE);

    UIData uidata = {};

    uidata.y = UI_SCREEN_HEIGHT * 2;
    uidata.x = UI_SCREEN_WIDTH * 8;
    for (int i = 0; i < SCORE_KIND_NUM; i++)
    {

        switch (i)
        {
        case ResultScore::collect:
            uidata.dataHandle = LoadGraph("data/CollectBonus.png");
            break;
        case ResultScore::hit:
            uidata.dataHandle = LoadGraph("data/Damage.png");
            break;
        case ResultScore::total:
            uidata.dataHandle = LoadGraph("data/Score.png");
            break;
        case ResultScore::time:
            uidata.dataHandle = LoadGraph("data/TimeBonus.png");
            break;
        default:
            break;
        }
        scoreUI[i].data = uidata;
        uidata.y += UI_SCREEN_HEIGHT * 4;
    }
    
    
    num = new NumUI();
    screenGraph = MakeGraph(SCREEN_WIDTH, SCREEN_HEIGHT);
    GetDrawScreenGraph(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, screenGraph);

    timer = new Timer(spaceKeyCoolTime);
}

PostGoalStaging::~PostGoalStaging()
{
    DeleteGraph(screenGraph);
    SAFE_DELETE(switchUI);
    SAFE_DELETE(stringUI);

}

bool PostGoalStaging::Update()
{

    if (x > SCREEN_WIDTH && !SoundPlayer::IsPlaySound(stopSE) && spaceClickCount < SCORE_KIND_NUM )
    {
        timer->Update();
        if (!SoundPlayer::IsPlaySound(rouretteSE))
        {
            SoundPlayer::Play2DSE(rouretteSE);
        }
        float larp = 1 - timer->GetLimitTime() / spaceKeyCoolTime;
        scoreUI[spaceClickCount].score = ResultScore::GetScore(spaceClickCount) * larp;
        if (UserInput::GetInputState(Space) == Detach || scoreUI[spaceClickCount].score == ResultScore::GetScore(spaceClickCount))
        {
            SoundPlayer::StopSound(rouretteSE);
            SoundPlayer::Play2DSE(stopSE);
            scoreUI[spaceClickCount].score = ResultScore::GetScore(spaceClickCount);

            spaceClickCount++;

            if (UserInput::GetInputState(Space) == Detach && spaceClickCount >= SCORE_KIND_NUM + 1)
            {
                return true;
            }
            timer->Init();
        }
    }
    else
    {
        x += goalMoveX;
        stringUI->SetXY(static_cast<int>(x), static_cast<int>(y));
    }
    
    switchUI->Update();
    return false;
}

void PostGoalStaging::Draw()
{
    SetDrawBright(60, 60, 60);
    DrawGraph(0, 0, screenGraph, false);
    SetDrawBright(255, 255, 255);
    if (x > SCREEN_WIDTH)
    {
        for (int i = 0; i <= spaceClickCount ; i++)
        {
            int safe_Num= i % SCORE_KIND_NUM;
            num->Draw(numDrawX, scoreUI[safe_Num].data.y, scoreUI[safe_Num].score, numSize);
            DrawRotaGraph(scoreUI[safe_Num].data.x, scoreUI[safe_Num].data.y, 1, 0, scoreUI[safe_Num].data.dataHandle, true);
        }

        if (spaceClickCount != 0)
        {
            switchUI->Draw();
        }
    }
    else
    {
        stringUI->DrawRightAlignedString();
    }
}
