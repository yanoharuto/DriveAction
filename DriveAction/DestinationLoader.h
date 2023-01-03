#pragma once
#include <vector>
#include<string>
#include "DxLib.h"
class DestinationLoader
{
public:
    DestinationLoader();
    ~DestinationLoader();
    void LoadCheckPoint(std::vector<VECTOR>* posVec, std::vector<VECTOR>* dirVec, std::string fileName);
};

