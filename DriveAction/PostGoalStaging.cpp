#include "PostGoalStaging.h"
#include "Utility.h"
#include "SoundPlayer.h"
#include "UserInput.h"
#include "ResultScore.h"
#include "RaceScreen.h"
PostGoalStaging::PostGoalStaging()
{
    SoundPlayer::StopAllSound();
    goalMarkerUI.x = 0;
    goalMarkerUI.y = SCREEN_HEIGHT / 2;
    goalMarkerUI.dataHandle = CreateFontToHandle("BIZ UDゴシック", 122, 3, DX_FONTTYPE_NORMAL);
    stringUI = new StringUI(goalMarkerUIColor, goalMarkerUI, "終了");
    switchUI = new SwitchUI();
    SoundPlayer::LoadSound(clapSE);
    SoundPlayer::LoadSound(rouretteSE);
    SoundPlayer::LoadSound(stopSE);
    SoundPlayer::LoadSound(nextSE);
    SoundPlayer::Play2DSE(clapSE);
    
    screenGraph = RaceScreen::GetRaceScreen();
    
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
    //終了のアナウンスの表示が終えたら
    if (goalMarkerUI.x > SCREEN_WIDTH && !SoundPlayer::IsPlaySound(stopSE) && spaceClickCount < SCORE_KIND_NUM )
    {
        timer->Update();
        if (!SoundPlayer::IsPlaySound(rouretteSE))
        {
            SoundPlayer::Play2DSE(rouretteSE);
        }
        //スコアの表示を少しずつしていく
        float larp = 1 - timer->GetLimitTime() / spaceKeyCoolTime;
        scoreUI[spaceClickCount].score = ResultScore::GetScore(spaceClickCount) * larp;
        //スコアを表示しきったら
        if (UserInput::GetInputState(Space) == Detach || scoreUI[spaceClickCount].score == ResultScore::GetScore(spaceClickCount))
        {
            //スコアの最終表示
            SoundPlayer::StopSound(rouretteSE);
            SoundPlayer::Play2DSE(stopSE);
            scoreUI[spaceClickCount].score = ResultScore::GetScore(spaceClickCount);
            //次のスコアの更新の準備
            spaceClickCount++;

            timer->Init();
        }
    }
    else//終了アナウンスを移動させる
    {
        goalMarkerUI.x += goalMoveX;
        stringUI->SetXY(goalMarkerUI.x, goalMarkerUI.y);
    }
    //スペースキー催促
    switchUI->Update();

    
    //終了時の音が鳴ってない時
    if (!SoundPlayer::IsPlaySound(nextSE))
    {
        
        //スコアを表示しきったら音を鳴らして
        if (spaceClickCount == SCORE_KIND_NUM && UserInput::GetInputState(Space))
        {
            SoundPlayer::Play2DSE(nextSE);
            spaceClickCount++;
            timer->Init();
        }
        //なり終わったら終了
        if (spaceClickCount > SCORE_KIND_NUM )
        {
            timer->Update();
            if (timer->IsOverLimitTime())
            {
                return true;
            }
        }
    }
    return false;
}

void PostGoalStaging::Draw()
{
    SetDrawBright(60, 60, 60);
    DrawGraph(0, 0, screenGraph, false);
    SetDrawBright(255, 255, 255);
    if (goalMarkerUI.x > SCREEN_WIDTH)
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

void PostGoalStaging::SetUp(int graphHandle)
{
    
}
