#pragma once
#include "StaticObject.h"

class Goal :
    public StaticObject
{
public:
    Goal();
    ~Goal();

private:
    VECTOR position;
    VECTOR direction;
};

