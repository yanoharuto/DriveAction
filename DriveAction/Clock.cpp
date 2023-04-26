#include "Clock.h"
#include "DxLib.h"
#include "Utility.h"

Clock::Clock()
{
    time = GetNowCount();
    startTime = GetNowCount();

    // ���݂̃J�E���g���擾����
    timeD = static_cast<double>(GetNowHiPerformanceCount());
}

Clock::~Clock()
{
}

/// <summary>
/// �^�C�}�[���X�V����
/// </summary>
void Clock::Update()
{
    // �P�V�~���b(��b�ԂU�O�t���[�����������̂P�t���[��������̌o�ߎ���)
    // �o�߂���܂ł����ő҂�
   double temp =  static_cast<double>(GetNowHiPerformanceCount()) - timeD;
    while (temp < DELTATIME)
    {
        temp =  static_cast<double>(GetNowHiPerformanceCount()) - timeD;
    }

    // ���݂̃J�E���g���擾����
    timeD =  static_cast<double>(GetNowHiPerformanceCount());
}

/// <summary>
/// �Q�[���J�n���Ă��牽�b����������
/// </summary>
/// <returns>�o�ߎ���</returns>
float Clock::GetScoreTime()
{
    return static_cast<int>(GetNowCount() - startTime);
}
