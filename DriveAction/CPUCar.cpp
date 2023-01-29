#include <math.h>
#include "CPUCar.h"
#include "Wheels.h"
#include "Utility.h"

/// <summary>
/// ������
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
/// <param nadme="outsideHitFlag">�R�[�X�O�ɏo����</param>
void CPUCar::Update(const float deltaTime, const bool outsideHitFlag, NeighborhoodInfo neighInfo, SoundPlayer* soundPlayer)
{
    AutoDrive(deltaTime, outsideHitFlag, neighInfo, soundPlayer);
}


void CPUCar::Init()
{
    modelHandle = MV1LoadModel("data/model/Player/RedCar.mv1");
}
