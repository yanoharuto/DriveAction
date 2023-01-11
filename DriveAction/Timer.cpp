#include "Timer.h"
#include "DxLib.h"
Timer::Timer()
{
    time = static_cast<float>(GetNowCount());
    deltaTime = deltaTimeCalculationLine;
    startTime = time;
}

Timer::~Timer()
{
}
/// <summary>
/// �^�C�}�[���X�V����
/// </summary>
void Timer::Update()
{
    while (deltaTimeCalculationLine < 0.001f)
    {
        deltaTimeCalculationLine = ((float)GetNowCount() - time) / Thousand;
    }

    while (deltaTime < deltaTimeCalculationLine)
    {
        deltaTime = ((float)GetNowCount() - time) / Thousand;
    }
#ifdef _DEBUG

    printfDx("%f,%f\n", deltaTime,deltaTimeCalculationLine);
#endif
    time = (float)GetNowCount();
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
