#pragma once
class Actor;
class Stage;
class ColiderChecker
{
public:
    ColiderChecker();
    ~ColiderChecker();
    void Check(Actor* const objA, Stage* const objB);
};

