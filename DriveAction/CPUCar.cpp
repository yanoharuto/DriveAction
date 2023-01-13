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
    float destinationDir = 0;//目的地との距離のずれ
    VECTOR distance = VSub(destinationPos, position);
    destinationDir = VDot(direction, distance) / (VSize(distance) * VSize(direction));
    destinationDir = acosf(destinationDir) / rage;
    //引数にして渡したい情報達
    ArgumentCarInfo info;
    if (destinationDir > turnProccesLine)
    {    
        //車の向いてる方向と目的地までの方向の外積を出して
        //右に曲がるか左に曲がるか調べる
        float crossY = VCross(VNorm(direction), VNorm(distance)).y;
        info.handleDir = crossY > 0 ? HandleDirection::right : HandleDirection::left;
    }
    else
    {
        info.handleDir = HandleDirection::straight;
    }
    UpdateVelocity(VScale(GetAccelVec(info.handleDir,outsideHitFlag,deltaTime),deltaTime));
    UpdateMV1Pos();
    ModelSetMatrix();
    info.matrix = MV1GetMatrix(modelHandle);
    info.velocitySize = VSize(velocity);
    info.direction = direction;

    wheels->WheelUpdate(info);
}

/// <summary>
/// 加速するための処理
/// </summary>
/// <param name="dir">向かってる方向</param>
/// <param name="outsideHitFlag"></param>
/// <returns></returns>
VECTOR CPUCar::GetAccelVec(HandleDirection handleDir, bool outsideHitFlag,float deltaTime)
{
    // 加速処理.
    VECTOR accelVec = VGet(0, 0, 0);
    accelPower += accelPower > maxSpeed ? 0 : accelSpeed * deltaTime;
    // 止まっている場合は減速しない.
    if (VSize(velocity) > 0)
    {
        //左右に曲がろうとしていたら減速
        if (handleDir!=HandleDirection::straight)
        {
            //左右に曲がろうとしたら減速する
            accelPower *= gripDecel * deltaTime;
        }
        //コース外に出たら減速
        if (outsideHitFlag)
        {
            accelPower *= outsideHitDecel * deltaTime;
        }
    }
    accelVec = VScale(direction, accelPower);
    return accelVec;
}

void CPUCar::Init()
{
    modelHandle = MV1LoadModel("data/model/Player/RedCar.mv1");
}
