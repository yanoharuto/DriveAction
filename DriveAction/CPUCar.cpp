#include "CPUCar.h"
#include "Wheels.h"
#include "Utility.h"
#include <math.h>
CPUCar::CPUCar()
{
    modelHandle = MV1LoadModel("data/model/Player/WhiteCar.mv1");
    position = firstPos;
    direction = firstDir;
    destinationPos = {};
}

CPUCar::~CPUCar()
{
    MV1DeleteModel(modelHandle);
    SAFE_DELETE(wheels)
}

void CPUCar::Update(const float deltaTime, const bool outsideHitFlag)
{
 
    float destinationDir = VCross(VNorm(direction),VNorm(VSub(destinationPos, position))).y;
    UpdateVelocity(deltaTime, GetAccelVec(destinationDir,outsideHitFlag));
    UpdateMV1Pos();
    ModelSetMatrix();
    ArgumentCarInfo info = { MV1GetMatrix(modelHandle),direction,VSize(velocity) };
    if (fabsf(destinationDir)>calculationLine)
    {
        info.handleDir = destinationDir > 0 ? HandleDirection::right : HandleDirection::left;
    }
    else
    {
        info.handleDir = HandleDirection::straight;
    }
    wheels->WheelUpdate(info);
}

void CPUCar::ConflictProcess(Object* object)
{
    ObjectTag tag = object->GetTag();
    if (tag == ObjectTag::goal)
    {
        destinationPos = object->GetPos();
    }
}

VECTOR CPUCar::GetAccelVec(const float dir,const bool outsideHitFlag)
{
    // 加速処理.
    VECTOR accelVec = VGet(0, 0, 0);
    accel += accel > maxSpeed ? 0 : accelSpeed;
    accelVec = VScale(direction, accel);
    // 止まっている場合は減速しない.
    if (VSize(velocity) > 0)
    {
        if (fabsf(dir) > calculationLine)
        {
            //左右に曲がろうとしたら減速する
            //CPUだから常時かかることにする
            accel += accel * gripDecel;
            accelVec = VScale(direction, accel);
        }
        //コース外に出たら減速
        if (outsideHitFlag)
        {
            accel += accel * outsideHitDecel;
            accelVec = VScale(direction, accel);
        }
    }
    return accelVec;
}