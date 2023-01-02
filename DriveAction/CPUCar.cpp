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
    modelHandle = MV1LoadModel("data/model/Player/RedCar.mv1");
    tag = ObjectTag::car;
    position = firstPos;
    direction = firstDir;
    destinationPos = {};
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
    
    //車の向いてる方向と目的地までの方向の外積を出して
    //右に曲がるか左に曲がるか調べる
    float destinationDir = VCross(VNorm(direction),VNorm(VSub(destinationPos, position))).y;
    UpdateVelocity(deltaTime, GetAccelVec(destinationDir,outsideHitFlag));
    UpdateMV1Pos();
    ModelSetMatrix();
    //引数にして渡したい情報達
    ArgumentCarInfo info = { MV1GetMatrix(modelHandle),direction,VSize(velocity) };
    if (fabsf(destinationDir)>turnProccesLine)
    {
        info.handleDir = destinationDir > 0 ? HandleDirection::right : HandleDirection::left;
    }
    else
    {
        info.handleDir = HandleDirection::straight;
    }
    wheels->WheelUpdate(info);
#ifdef _DEBUG
    printfDx("%f,%f\n", position.x, position.z);
    printfDx("%f,%f\n", destinationPos.x, destinationPos.z);
#endif
}

/// <summary>
/// 加速するための処理
/// </summary>
/// <param name="dir">向かってる方向</param>
/// <param name="outsideHitFlag"></param>
/// <returns></returns>
VECTOR CPUCar::GetAccelVec(const float dir,const bool outsideHitFlag)
{
    // 加速処理.
    VECTOR accelVec = VGet(0, 0, 0);
    accelPower += accelPower > maxSpeed ? 0 : accelSpeed;
    // 止まっている場合は減速しない.
    if (VSize(velocity) > 0)
    {
        if (fabsf(dir) > turnProccesLine)
        {
            //左右に曲がろうとしたら減速する
            //CPUだから常時かかることにする
            accelPower -= accelPower * gripDecel;
        }
        //コース外に出たら減速
        if (outsideHitFlag)
        {
            accelPower -= accelPower * outsideHitDecel;
        }
    }
    accelVec = VScale(direction, accelPower);
    return accelVec;
}