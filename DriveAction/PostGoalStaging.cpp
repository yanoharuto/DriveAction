#include <iostream>
#include "PostGoalStaging.h"
#include "Utility.h"
#include "SoundPlayer.h"
#include "UserInput.h"
#include "ResultScore.h"
#include "RaceScreen.h"
#include "SwitchUI.h"
#include "NumUI.h"
PostGoalStaging::PostGoalStaging()
{
    SoundPlayer::StopAllSound();
    switchUI = new SwitchUI();
    SoundPlayer::LoadSound(clapSE);
    SoundPlayer::LoadSound(rouretteSE);
    SoundPlayer::LoadSound(stopSE);
    SoundPlayer::LoadSound(nextSE);
    SoundPlayer::Play2DSE(clapSE);
    
    screenGraph = RaceScreen::GetRaceScreen();

    InitScoreUI(collectScore, 0);
    InitScoreUI(damageScore, 1);
    InitScoreUI(totalScore, 2);
    InitScoreUI(timeScore, 3);
    //Y座標が高い順にソート
    for (int i = 0; i < SCORE_KIND_NUM; i++)
    {
        int iY = scoreUI[i].data.y;
        for (int j = i; j < SCORE_KIND_NUM; j++)
        {
            int jY = scoreUI[j].data.y;
            //i番目の要素を決める
            if (jY < iY)
            {
                std::swap(scoreUI[j],scoreUI[i] );
            }
        }
    }
    timer = new Timer(spaceKeyCoolTime);
}

PostGoalStaging::~PostGoalStaging()
{
    DeleteGraph(screenGraph);
    SAFE_DELETE(switchUI);
}

bool PostGoalStaging::Update()
{
    //終了のアナウンスの表示が終えたら
    if (!SoundPlayer::IsPlaySound(stopSE) && spaceClickCount < SCORE_KIND_NUM )
    {
        if (!SoundPlayer::IsPlaySound(rouretteSE))
        {
            SoundPlayer::Play2DSE(rouretteSE);
        }
        //スコアの表示を少しずつしていく
        float larp = 1 - timer->GetLimitTime() / spaceKeyCoolTime;
        scoreUI[spaceClickCount].score = static_cast<int>(ResultScore::GetScore(spaceClickCount) * larp);
        //スコアを表示しきるかボタンを押されたら
        if (UserInput::GetInputState(Space) == Detach || timer->IsOverLimitTime())
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

    for (int i = 0; i <= spaceClickCount; i++)
    {
        int safeNum = i % SCORE_KIND_NUM;
        scoreUI[safeNum].ui->Draw(scoreUI[safeNum].score);
        DrawRotaGraph(scoreUI[safeNum].data.x, scoreUI[safeNum].data.y, scoreUI[safeNum].data.size, 0, scoreUI[safeNum].data.dataHandle[0], true);
    }

    if (spaceClickCount != 0)
    {
        switchUI->Draw();
    }
}

void PostGoalStaging::InitScoreUI(UIKind kind,int index)
{
    switch (kind)
    {
    case collectScore:
        scoreUI[index].data = UIManager::CreateUIData(collectScore);
        scoreUI[index].ui = new NumUI(collectScoreNum);
        break;
    case timeScore:
        scoreUI[index].data = UIManager::CreateUIData(timeScore);
        scoreUI[index].ui = new NumUI(timeScoreNum);
        break;
    case totalScore:
        scoreUI[index].data = UIManager::CreateUIData(totalScore);
        scoreUI[index].ui = new NumUI(totalScoreNum);
        break;
    case damageScore:
        scoreUI[index].data = UIManager::CreateUIData(damageScore);
        scoreUI[index].ui = new NumUI(damageScoreNum);
        break;
    }
}
