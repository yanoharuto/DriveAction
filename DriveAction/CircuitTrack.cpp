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
    MV1SetPosition(outsideModelHandle, outsideModelPosition);    //�኱�R�[�X�̊O����������
    //�傫���ύX
    VECTOR scale = VGet(courceModelScaleValue, courceModelScaleValue, courceModelScaleValue);
    MV1SetScale(courceModelHandle, scale);
    scale = VGet(outsideModelScaleValue, outsideModelScaleValue, outsideModelScaleValue);
    MV1SetScale(outsideModelHandle, scale);
    //�h�ǂ̔��a
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
    //�ǂɂԂ��������֐��ɂ�����
    MV1_COLL_RESULT_POLY_DIM polyInfo;
    polyInfo = MV1CollCheck_Sphere(courceModelHandle, -1, car->GetPos(),car->GetRadius());

    //�������Ă鎞�͓��������ꏊ��Ԃ�
    if (polyInfo.HitNum != 0)
    {
        VECTOR hitPos = polyInfo.Dim->HitPosition;
        MV1CollResultPolyDimTerminate(polyInfo);
        return { true,tag,hitPos,radius };
    }
  
    return {};
}

/// <summary>
/// �R�[�X�̃��f����`��
/// </summary>
void CircuitTrack::Draw()
{
  MV1DrawModel(courceModelHandle);
  MV1DrawModel(outsideModelHandle);
}
