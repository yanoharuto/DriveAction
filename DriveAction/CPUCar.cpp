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
    // ��������.
    VECTOR accelVec = VGet(0, 0, 0);
    accel += accel > maxSpeed ? 0 : accelSpeed;
    accelVec = VScale(direction, accel);
    // �~�܂��Ă���ꍇ�͌������Ȃ�.
    if (VSize(velocity) > 0)
    {
        if (fabsf(dir) > calculationLine)
        {
            //���E�ɋȂ��낤�Ƃ����猸������
            //CPU������펞�����邱�Ƃɂ���
            accel += accel * gripDecel;
            accelVec = VScale(direction, accel);
        }
        //�R�[�X�O�ɏo���猸��
        if (outsideHitFlag)
        {
            accel += accel * outsideHitDecel;
            accelVec = VScale(direction, accel);
        }
    }
    return accelVec;
}