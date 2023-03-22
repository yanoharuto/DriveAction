#pragma once

/// <summary>
/// �o�ߎ��Ԃ�f���^�^�C�����o����
/// </summary>
class Timer
{
public:
    Timer();
    Timer(float limitTime);
    ~Timer();
    void Update(float deltaTime);
    void Init();
    bool IsOverLimitTime();

private:
    float limitTime = 0;
    float elapsedTime = 0;
};

