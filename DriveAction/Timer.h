#pragma once

/// <summary>
/// ���߂�ꂽ���Ԑi�񂾂肷��
/// </summary>
class Timer
{
public:
    Timer();
    Timer(float limitTime);
    ~Timer();
    //�f���^�^�C�������Z
    void Update();
    void Init();
    bool IsOverLimitTime();
    float GetLimitTime();
private:
    float limitTime = 0;
    float elapsedTime = 0;
};

