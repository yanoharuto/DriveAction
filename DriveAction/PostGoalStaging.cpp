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
    //Y���W���������Ƀ\�[�g
    for (int i = 0; i < SCORE_KIND_NUM; i++)
    {
        int iY = scoreUI[i].data.y;
        for (int j = i; j < SCORE_KIND_NUM; j++)
        {
            int jY = scoreUI[j].data.y;
            //i�Ԗڂ̗v�f�����߂�
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
    //�I���̃A�i�E���X�̕\�����I������
    if (!SoundPlayer::IsPlaySound(stopSE) && spaceClickCount < SCORE_KIND_NUM )
    {
        if (!SoundPlayer::IsPlaySound(rouretteSE))
        {
            SoundPlayer::Play2DSE(rouretteSE);
        }
        //�X�R�A�̕\�������������Ă���
        float larp = 1 - timer->GetLimitTime() / spaceKeyCoolTime;
        scoreUI[spaceClickCount].score = static_cast<int>(ResultScore::GetScore(spaceClickCount) * larp);
        //�X�R�A��\�������邩�{�^���������ꂽ��
        if (UserInput::GetInputState(Space) == Detach || timer->IsOverLimitTime())
        {
            //�X�R�A�̍ŏI�\��
            SoundPlayer::StopSound(rouretteSE);
            SoundPlayer::Play2DSE(stopSE);
            scoreUI[spaceClickCount].score = ResultScore::GetScore(spaceClickCount);
            //���̃X�R�A�̍X�V�̏���
            spaceClickCount++;

            timer->Init();
        }
    }
    else//�I���A�i�E���X���ړ�������
    {
    }
    //�X�y�[�X�L�[�Ñ�
    switchUI->Update();

    
    //�I�����̉������ĂȂ���
    if (!SoundPlayer::IsPlaySound(nextSE))
    {
        
        //�X�R�A��\�����������特��炵��
        if (spaceClickCount == SCORE_KIND_NUM && UserInput::GetInputState(Space))
        {
            SoundPlayer::Play2DSE(nextSE);
            spaceClickCount++;
            timer->Init();
        }
        //�Ȃ�I�������I��
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
