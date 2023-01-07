#pragma once
#include <vector>
#include<string>
#include "DxLib.h"
class VECTOR3Loader
{
public:
    VECTOR3Loader();
    ~VECTOR3Loader();
    void LoadCheckPoint(std::vector<VECTOR>* posVec, std::vector<VECTOR>* dirVec, std::string fileName);
};

