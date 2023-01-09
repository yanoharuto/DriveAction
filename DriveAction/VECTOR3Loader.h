#pragma once
#include <list>
#include<string>
#include "DxLib.h"
class VECTOR3Loader
{
public:
    VECTOR3Loader();
    VECTOR3Loader(std::string fileName);
    ~VECTOR3Loader();
    std::list<VECTOR>::iterator GetVectorListIterator();
    std::list<VECTOR> GetVectorList();
private:
    void LoadVectorData(std::string fileName);
    std::list<VECTOR> vectorList;
};

