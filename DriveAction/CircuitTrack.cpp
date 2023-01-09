#include "CircuitTrack.h"
#include "Car.h"
/// <summary>
/// ������
/// </summary>
/// <param name="player">�v���C���[�̕������</param>
/// <returns></returns>
CircuitTrack::CircuitTrack(std::string courceModelAdress, std::string outsideModelAdress)
{
    courceModelHandle = MV1LoadModel(courceModelAdress.c_str());
    outsideModelHandle = MV1LoadModel(outsideModelAdress.c_str());
    //�኱�R�[�X�̊O����������
    MV1SetPosition(outsideModelHandle, outsideModelPosition);
    VECTOR scale = VGet(courceModelScaleValue, courceModelScaleValue, courceModelScaleValue);
    MV1SetScale(courceModelHandle, scale);
    scale = VGet(outsideModelScaleValue, outsideModelScaleValue, outsideModelScaleValue);
    MV1SetScale(outsideModelHandle, scale);
    radius = gurdRadius;
    tag = ObjectTag::stage;
}
/// <summary>
/// model�̉���@�R���W������������
/// </summary>
/// <returns></returns>
CircuitTrack::~CircuitTrack()
{
    MV1DeleteModel(courceModelHandle);
    MV1DeleteModel(outsideModelHandle);
}
/// <summary>
/// �R�[�X�̊O���ɓ������Ă邩���ׂ�
/// </summary>
/// <param name="actor">�O���ɂ��邩���ׂ�������</param>
/// <returns>�R�[�X�̊O���ɂ���Ȃ�True</returns>
bool CircuitTrack::GetOutsideHitFlag(Car* car)const
{
    //�����̎n�܂�ƏI�������
    //���Ƃ����W������Ă���
    VECTOR startPos = car->GetPos();
    startPos.y = sY;
    VECTOR endPos = startPos;
    endPos.y = eY;
    //�O���ɂ��邩���ׂ�
    DxLib::MV1_COLL_RESULT_POLY polyInfo = MV1CollCheck_Line(outsideModelHandle, -1, startPos, endPos);
    return polyInfo.HitFlag;
}
/// <summary>
/// �R�[�X�̕ǂɂԂ����Ă邩���ׂ�
/// </summary>
/// <param name="Actor">�Ԃ����Ă邩���ׂ�������</param>
/// <returns>�Ԃ����Ă���True</returns>
ArgumentConflictInfo  CircuitTrack::GetCourceConflictInfo(Car* car) const
{
    //�����̎n�܂�ƏI�������
    //���Ƃ����W������Ă���
    VECTOR startPos = car->GetPos();
    VECTOR endPos = startPos;
    float totalRad = car->GetRadius() + radius;
    startPos.x += totalRad;
    startPos.z += totalRad;
    endPos.x -= totalRad;
    endPos.z -= totalRad;
    //�ǂɂԂ�������
    MV1_COLL_RESULT_POLY polyInfo = MV1CollCheck_Line(courceModelHandle,-1, startPos, endPos, -1);
    if (!polyInfo.HitFlag)
    {
        return{};
    }
    return { true,tag,polyInfo.HitPosition,radius };
}

/// <summary>
/// �R�[�X�̃��f����`��
/// </summary>
void CircuitTrack::Draw()
{
    MV1DrawModel(courceModelHandle);
    MV1DrawModel(outsideModelHandle);
}
