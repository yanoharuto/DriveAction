#include "CircuitTrack.h"
#include <math.h>
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
bool CircuitTrack::GetOutsideHitFlag(ArgumentConflictInfo info)const
{
    //�����̎n�܂�ƏI�������
    //���Ƃ����W������Ă���
    VECTOR startPos = info.pos;
    startPos.y = sY;
    VECTOR endPos = info.pos;
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
ArgumentConflictInfo  CircuitTrack::GetCourceConflictInfo(ArgumentConflictInfo info) const
{
    //�ǂɂԂ��������֐��ɂ�����
    MV1_COLL_RESULT_POLY_DIM polyInfo;
    polyInfo = MV1CollCheck_Sphere(courceModelHandle, -1,info.pos,info.radius);

    //�������Ă鎞�͓��������ꏊ��Ԃ�
    if (polyInfo.HitNum != 0)
    {
        VECTOR hitPos = polyInfo.Dim->HitPosition;
        MV1CollResultPolyDimTerminate(polyInfo);
        return { true,tag,hitPos,radius };
    }
  
    return {};
}

NeighborhoodInfo CircuitTrack::GetObjNeighbornhoodInfo(CarNeighborhoodExamineInfo examineInfo) const
{
    NeighborhoodInfo returnValueInfo;
    for (int i = 0; i < 3; i++)
    {
        switch (i)
        {
        case 0:
            returnValueInfo.diagonallyForwardLeft = SetNeighbornhoodSituation(examineInfo, 0.5f);
        case 1:
            returnValueInfo.diagonallyForwardRight = SetNeighbornhoodSituation(examineInfo, -0.5f);
        case 2:
            returnValueInfo.forward = SetNeighbornhoodSituation(examineInfo);
        default:
            break;
        }
    }
    return returnValueInfo;
}

/// <summary>
/// �R�[�X�̃��f����`��
/// </summary>
void CircuitTrack::Draw()
{
    MV1DrawModel(courceModelHandle);
}

NeighborhoodSituation CircuitTrack::SetNeighbornhoodSituation(CarNeighborhoodExamineInfo examineInfo, float crossY) const
{
    //�����̎n�܂�ƏI�������
        //���Ƃ����W������Ă���
    VECTOR startPos = examineInfo.pos;
    VECTOR endPos = VCross(examineInfo.dir,VGet(0,crossY,0));
    endPos = VScale(endPos, examineInfo.range);
    endPos.y = eY;
    //�O���ɂ��邩���ׂ�
    DxLib::MV1_COLL_RESULT_POLY polyInfo = MV1CollCheck_Line(outsideModelHandle, -1, startPos, endPos);
    if (polyInfo.HitFlag)
    {
        return  NeighborhoodSituation::outside;
    }

    return NeighborhoodSituation::cource;

}

NeighborhoodSituation CircuitTrack::SetNeighbornhoodSituation(CarNeighborhoodExamineInfo examineInfo) const
{
    //�����̎n�܂�ƏI�������
    //���Ƃ����W������Ă���
    VECTOR startPos = examineInfo.pos;
    VECTOR endPos = examineInfo.dir;

    endPos = VScale(endPos, examineInfo.range);
    endPos.y = eY;
    //�O���ɂ��邩���ׂ�
    DxLib::MV1_COLL_RESULT_POLY polyInfo = MV1CollCheck_Line(outsideModelHandle, -1, startPos, endPos);
    if (polyInfo.HitFlag)
    {
        return  NeighborhoodSituation::outside;
    }

    return NeighborhoodSituation::cource;
}
