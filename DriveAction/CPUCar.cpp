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
    Init();
}
CPUCar::CPUCar(VECTOR firstPos, VECTOR firstDir,VECTOR destinationPos,SoundPlayer* soundPlayer)
    :Car(firstPos,firstDir, destinationPos,soundPlayer)
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
/// <param nadme="outsideHitFlag">コース外に出たか</param>
void CPUCar::Update(const float deltaTime, const bool outsideHitFlag, VECTOR pos, SoundPlayer* soundPlayer)
{
    AutoDrive(deltaTime, outsideHitFlag, pos, soundPlayer);
    printfDx("count%d\n", checkCount);
    if (checkCount % 4 == 3)
    {
        carMode = CarMode::flying;
        flyTime = maxFlyTime;
    }
    FlyUpdate(deltaTime);

}


void CPUCar::Init()
{
    modelHandle = MV1LoadModel("data/model/Player/RedCar.mv1");
    carMode = CarMode::normal;
}


