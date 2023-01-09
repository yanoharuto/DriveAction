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
    float time;
    bool countDownEnd;
};

