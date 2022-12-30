#pragma once
class Actor;
class Stage;
class ColiderChecker
{
public:
    ColiderChecker();
    ~ColiderChecker();
    void CheckConflictStage(Actor* const objA, Stage* const objB);
};

