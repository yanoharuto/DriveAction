#pragma once
#include <string>
class CountDown
{
public:
    CountDown();
    ~CountDown();
    std::string Update(float deltaTime);
    bool CountDownEnd();
private:
    float startTime;
    bool countDownEnd;
    int fiveTime = 5;
};

