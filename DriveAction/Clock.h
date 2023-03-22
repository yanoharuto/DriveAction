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
    /// �f���^�^�C�����o����
    /// </summary>
    /// <returns></returns>
    float GetDeltaTime();
    /// <summary>
    /// �Q�[���J�n���Ă��牽�b����������
    /// </summary>
    /// <returns>�o�ߎ���</returns>
    float GetScoreTime();

private:
    int FPS = 0;
    int FPSCounter = 0;
    float FPSCheckTime = 0;
    const float thousand = 1000;
    const float setDeltaTime = 0.016667f;
    int startTime;
    int time;
    float deltaTime;
    double timeD;
    //fps�̃J�E���^�A60�t���[����1���ƂȂ鎞�����L�^����ϐ�
    int fpsCount, countZeroT;
    //���ς��v�Z���邽��60���1�����Ԃ��L�^
    int f[FLAME];
    //����fps
    double averageFPS;
};