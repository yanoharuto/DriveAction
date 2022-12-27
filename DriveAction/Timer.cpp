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
    deltaTime = (GetNowCount() - time) / Thousand;
    if (deltaTime < deltaTimeCalculationLine)
    {
        deltaTime = deltaTimeCalculationLine;
    }
    time = GetNowCount();
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
