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
    float deltaTimeCalculationLine = 0;
    float startTime;
    float time;
    float deltaTime;
};

