#include <math.h>
#include "CPUCar.h"
#include "Wheels.h"
#include "Utility.h"

/// <summary>
/// 初期化
/// </summary>
/// <returns></returns>
CPUCar::CPUCar()
{
}
CPUCar::CPUCar(CarParamater carParam, VECTOR destinaTionPos, int duplicateModelHandle)
    :Car(carParam, duplicateModelHandle)
{
    destinationPos = destinaTionPos;
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
/// <param nadme="outsideHitFlag">コース外に出たか</param>
void CPUCar::Update(const float deltaTime, const bool outsideHitFlag, ItemInfo itemInfo)
{
    AutoDrive(deltaTime, outsideHitFlag,itemInfo);
}