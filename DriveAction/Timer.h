#pragma once
/// <summary>
/// �o�ߎ��Ԃ�f���^�^�C�����o����
/// </summary>
class Timer
{
public:
    Timer();
    ~Timer();
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
    const float Thousand = 1000;
    const float deltaTimeCalculationLine = 0.00001f;
    float startTime;
    float time;
    float deltaTime;
};

