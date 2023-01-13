#include "CPUCar.h"
#include "Wheels.h"
#include "Utility.h"
#include <math.h>
/// <summary>
/// ������
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
/// model�ƃ^�C���̌�n��
/// </summary>
/// <returns></returns>
CPUCar::~CPUCar()
{
    MV1DeleteModel(modelHandle);
    SAFE_DELETE(wheels)
}
/// <summary>
/// �������c�B
/// </summary>
/// <param name="deltaTime">�t���[���ԍ���</param>
/// <param name="outsideHitFlag">�R�[�X�O�ɏo����</param>
void CPUCar::Update(const float deltaTime, const bool outsideHitFlag)
{
    float destinationDir = 0;//�ړI�n�Ƃ̋����̂���
    VECTOR distance = VSub(destinationPos, position);
    destinationDir = VDot(direction, distance) / (VSize(distance) * VSize(direction));
    destinationDir = acosf(destinationDir) / rage;
    //�����ɂ��ēn���������B
    ArgumentCarInfo info;
    if (destinationDir > turnProccesLine)
    {    
        //�Ԃ̌����Ă�����ƖړI�n�܂ł̕����̊O�ς��o����
        //�E�ɋȂ��邩���ɋȂ��邩���ׂ�
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
/// �������邽�߂̏���
/// </summary>
/// <param name="dir">�������Ă����</param>
/// <param name="outsideHitFlag"></param>
/// <returns></returns>
VECTOR CPUCar::GetAccelVec(HandleDirection handleDir, bool outsideHitFlag,float deltaTime)
{
    // ��������.
    VECTOR accelVec = VGet(0, 0, 0);
    accelPower += accelPower > maxSpeed ? 0 : accelSpeed * deltaTime;
    // �~�܂��Ă���ꍇ�͌������Ȃ�.
    if (VSize(velocity) > 0)
    {
        //���E�ɋȂ��낤�Ƃ��Ă����猸��
        if (handleDir!=HandleDirection::straight)
        {
            //���E�ɋȂ��낤�Ƃ����猸������
            accelPower *= gripDecel * deltaTime;
        }
        //�R�[�X�O�ɏo���猸��
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
