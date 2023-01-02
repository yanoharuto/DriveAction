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
    modelHandle = MV1LoadModel("data/model/Player/RedCar.mv1");
    tag = ObjectTag::car;
    position = firstPos;
    direction = firstDir;
    destinationPos = {};
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
    
    //�Ԃ̌����Ă�����ƖړI�n�܂ł̕����̊O�ς��o����
    //�E�ɋȂ��邩���ɋȂ��邩���ׂ�
    float destinationDir = VCross(VNorm(direction),VNorm(VSub(destinationPos, position))).y;
    UpdateVelocity(deltaTime, GetAccelVec(destinationDir,outsideHitFlag));
    UpdateMV1Pos();
    ModelSetMatrix();
    //�����ɂ��ēn���������B
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
/// �������邽�߂̏���
/// </summary>
/// <param name="dir">�������Ă����</param>
/// <param name="outsideHitFlag"></param>
/// <returns></returns>
VECTOR CPUCar::GetAccelVec(const float dir,const bool outsideHitFlag)
{
    // ��������.
    VECTOR accelVec = VGet(0, 0, 0);
    accelPower += accelPower > maxSpeed ? 0 : accelSpeed;
    // �~�܂��Ă���ꍇ�͌������Ȃ�.
    if (VSize(velocity) > 0)
    {
        if (fabsf(dir) > turnProccesLine)
        {
            //���E�ɋȂ��낤�Ƃ����猸������
            //CPU������펞�����邱�Ƃɂ���
            accelPower -= accelPower * gripDecel;
        }
        //�R�[�X�O�ɏo���猸��
        if (outsideHitFlag)
        {
            accelPower -= accelPower * outsideHitDecel;
        }
    }
    accelVec = VScale(direction, accelPower);
    return accelVec;
}