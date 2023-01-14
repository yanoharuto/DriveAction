#include "CPUCar.h"
#include "Wheels.h"
#include "Utility.h"
#include <math.h>
/// <summary>
/// 初期化
/// </summary>
/// <returns></returns>
CPUCar::CPUCar()
{
    Init();
}
CPUCar::CPUCar(VECTOR firstPos, VECTOR firstDir)
    :Car(firstPos,firstDir)
{
    Init();
}
/// <summary>
/// modelとタイヤの後始末
/// </summary>
/// <returns></returns>
CPUCar::~CPUCar()
{
    MV1DeleteModel(modelHandle);
    SAFE_DELETE(wheels)
}
/// <summary>
/// 自動操縦。
/// </summary>
/// <param name="deltaTime">フレーム間差分</param>
/// <param name="outsideHitFlag">コース外に出たか</param>
void CPUCar::Update(const float deltaTime, const bool outsideHitFlag)
{
    AutoDrive(deltaTime,outsideHitFlag);
}


void CPUCar::Init()
{
    modelHandle = MV1LoadModel("data/model/Player/RedCar.mv1");
}
