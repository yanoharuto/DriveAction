#pragma once

//fps
#define FLAME 60
class Clock
{
public:
    Clock();
    ~Clock();
    /// <summary>
    /// �^�C�}�[���X�V����
    /// </summary>
    void Update();

    /// <summary>
    /// �Q�[���J�n���Ă��牽�b����������
    /// </summary>
    /// <returns>�o�ߎ���</returns>
    float GetScoreTime();

private:
    int startTime;
    int time;
    double timeD;
};