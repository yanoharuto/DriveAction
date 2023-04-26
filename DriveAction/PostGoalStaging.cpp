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
    
    UIData uidata = {};

    uidata.y = UI_SCREEN_HEIGHT * 2;
    uidata.x = UI_SCREEN_WIDTH * 8;
    for (int i = 0; i < SCORE_KIND_NUM; i++)
    {
        switch (i)
        {
        case ResultScore::collect:
            uidata = UIManager::CreateUIData(collectScore);
            break;
        case ResultScore::hit:
            uidata = UIManager::CreateUIData(damageScore);
            break;
        case ResultScore::total:
            uidata = UIManager::CreateUIData(totalScore);
            break;
        case ResultScore::time:
            uidata = UIManager::CreateUIData(timeScore);
            break;
        default:
            break;
        }
        scoreUI[i].data = uidata;
    }
    num = new NumUI();
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
        timer->Update();
        if (!SoundPlayer::IsPlaySound(rouretteSE))
        {
            SoundPlayer::Play2DSE(rouretteSE);
        }
        //�X�R�A�̕\�������������Ă���
        float larp = 1 - timer->GetLimitTime() / spaceKeyCoolTime;
        scoreUI[spaceClickCount].score = ResultScore::GetScore(spaceClickCount) * larp;
        //�X�R�A��\������������
        if (UserInput::GetInputState(Space) == Detach || scoreUI[spaceClickCount].score == ResultScore::GetScore(spaceClickCount))
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

    for (int i = 0; i <= spaceClickCount; i++)
    {
        int safeNum = i % SCORE_KIND_NUM;
        num->Draw(numDrawX, scoreUI[safeNum].data.y, scoreUI[safeNum].score, numSize);
        DrawRotaGraph(scoreUI[safeNum].data.x, scoreUI[safeNum].data.y, scoreUI[safeNum].data.size, 0, scoreUI[safeNum].data.dataHandle[0], true);
    }

    if (spaceClickCount != 0)
    {
        switchUI->Draw();
    }
}
