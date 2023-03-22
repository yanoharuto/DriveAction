#pragma once
#include "ItemArgumentCarInfo.h"
#include "DxLib.h"
class ModelUpdater
{
public:
    ModelUpdater();
    ModelUpdater(int setModelHandle);
    ~ModelUpdater();
    void ModelSetMatrix(ItemArgumentCarInfo objInfo);
    void UpdateMV1Pos(VECTOR position);
    void SetScale(VECTOR scale);
private:
    int modelHandle;
};