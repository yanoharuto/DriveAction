#include "Timer.h"
#include "DxLib.h"
#include "Utility.h"
/// <summary>
/// �������ԂƂ����v������
/// </summary>
/// <param name="setLimitTime"></param>
Timer::Timer(float setLimitTime)
{
    limitTime = setLimitTime;
    startTime = static_cast<double>(GetNowHiPerformanceCount());
}

Timer::~Timer()
{
}
/// <summary>
/// ���Ԃ����Z�b�g
/// </summary>
void Timer::Init()
{
    startTime = static_cast<double>(GetNowHiPerformanceCount());
}
/// <summary>
/// �ݒ莞�Ԃ��߂�����
/// </summary>
/// <returns>�߂�����True</returns>
bool Timer::IsOverLimitTime()
{
    //�o�ߎ���
    double elaspedTime = static_cast<double>(GetNowHiPerformanceCount()) - startTime;
    return limitTime < elaspedTime / 1000000;
}
/// <summary>
/// �v������
/// </summary>
/// <returns></returns>
float Timer::GetLimitTime()
{
    //�o�ߎ���
    double elaspedTime = static_cast<double>(GetNowHiPerformanceCount()) - startTime;
    return limitTime - static_cast<float>(elaspedTime / 1000000);;
}
