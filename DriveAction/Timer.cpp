#include "Timer.h"
#include "DxLib.h"
Timer::Timer()
{
    time = 0;
    deltaTime = deltaTimeCalculationLine;
    startTime = GetNowCount();
    fpsCount = 0;
    averageFPS = 0;
}

Timer::~Timer()
{
}
/// <summary>
/// �^�C�}�[���X�V����
/// </summary>
void Timer::Update()
{
    int term, nowCount;

    if (fpsCount == 0) 
    {
        //60�t���[����1��ڂȂ�
        if (time == 0)//���S�ɍŏ��Ȃ�܂��Ȃ�
        {
            term = 0;
        }
        else//�O��L�^�������Ԃ����Ɍv�Z
        {
            term = countZeroT + thousand - GetNowCount();
        }
    }
    else    //�҂ׂ�����=���݂���ׂ�����-���݂̎���
    {
        term = (int)(countZeroT + fpsCount * (thousand / FLAME)) - GetNowCount();
    }

    if (term > 0)//�҂ׂ����Ԃ����҂�
    {
        Sleep(term);
    }
    nowCount = GetNowCount();

    if (fpsCount == 0)//60�t���[����1�x������
    {
        countZeroT = nowCount;
    }
    f[fpsCount] = nowCount - time;//�P���������Ԃ��L�^
    deltaTime = (nowCount - time) / thousand;
    time = nowCount;
    //���όv�Z
    if (fpsCount == FLAME - 1) {
        averageFPS = 0;
        //���v���Ċ���
        for (int i = 0; i < FLAME; i++)
        {
            averageFPS += f[i];
        }
        averageFPS /= FLAME;
    }
    fpsCount = (++fpsCount) % FLAME;

    
#ifdef _DEBUG

   // printfDx("deltaTime,%f::FPS,%d\n", deltaTime, fpsCount);

#endif
}
/// <summary>
/// �f���^�^�C�����o����
/// </summary>
/// <returns></returns>
float Timer::GetDeltaTime()
{
    return deltaTime;
}

/// <summary>
/// �Q�[���J�n���Ă��牽�b����������
/// </summary>
/// <returns>�o�ߎ���</returns>
float Timer::GetScoreTime()
{
    return GetNowCount() - startTime;
}
