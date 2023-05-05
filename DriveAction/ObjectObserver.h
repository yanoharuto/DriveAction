#pragma once
#include "DxLib.h"
#include <string>
#include "Object.h"
class ObjectObserver
{
public:
    ObjectObserver();
    ~ObjectObserver();
    VECTOR GetSubPos();
    VECTOR GetSubDir();
    int GetObjHitCount(Object::ObjectTag objTag);
};

