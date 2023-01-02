#pragma once
class Object;
class HitChecker
{
public:
    HitChecker();
    ~HitChecker();
    bool HitCheck(Object* const objA, Object* const objB);
};

