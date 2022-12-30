#pragma once
#include "Actor.h"

class Stage :
    public Object
{
public:
    Stage() {};
    ~Stage() {};
    virtual void ConflictProcess(Actor* actor) {};
};