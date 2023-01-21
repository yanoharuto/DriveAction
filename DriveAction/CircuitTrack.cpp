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
bool CircuitTrack::GetOutsideHitFlag(ConflictProccessArgumentInfo info)const
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
ConflictProccessArgumentInfo  CircuitTrack::GetCourceConflictInfo(ConflictProccessArgumentInfo info) const
{
    //
    CarNeighborhoodExamineInfo examineInfo = { info.pos,info.radius };
    ConflictProccessArgumentInfo conflictInfo = GetSphereConflictModelInfo(courceModelHandle, examineInfo);
    //�������Ă鎞
    if (conflictInfo.hitFlag)
    {
        conflictInfo.radius = radius;
        conflictInfo.tag = tag;
        return conflictInfo;
    }
  
    return { false,tag,{},radius };
}

/// <summary>
/// �����͈̔͂ɉ������邩���ׂ��
/// </summary>
/// <param name="examineInfo"></param>
/// <returns></returns>
NeighborhoodInfo CircuitTrack::GetOutsideExamineInfo(CarNeighborhoodExamineInfo examineInfo) const
{
    NeighborhoodInfo returnValueInfo;
    returnValueInfo.outside = GetSphereConflictModelInfo(outsideModelHandle,examineInfo);
    CarNeighborhoodExamineInfo examineInfo2 = examineInfo;
    examineInfo2.pos.y = outsideModelPosition.y;
    returnValueInfo.obstacle = GetSphereConflictModelInfo(courceModelHandle, examineInfo2);
    return returnValueInfo;
}

/// <summary>
/// �R�[�X�̃��f����`��
/// </summary>
void CircuitTrack::Draw()
{
    MV1DrawModel(courceModelHandle);
}
/// <summary>
/// MV1CollCheck_Sphere���g���ă��f���n���h�����˒��������ׂ��
/// </summary>
/// <param name="modelHandle">���ׂ郂�f��</param>
/// <param name="examineInfo">���ׂ邽�߂ɕK�v�ȏ��</param>
/// <returns>�Ԃ������ʒu��Ԃ���B�Ԃ����ĂȂ��Ȃ�HitFlag��false</returns>
ConflictProccessArgumentInfo CircuitTrack::GetSphereConflictModelInfo(int modelHandle,CarNeighborhoodExamineInfo examineInfo) const
{
    DxLib::MV1_COLL_RESULT_POLY_DIM polyInfo = MV1CollCheck_Sphere(modelHandle, -1, examineInfo.pos, examineInfo.range);
    ConflictProccessArgumentInfo conflictPos = {};
    if (polyInfo.HitNum!=0)
    {
        conflictPos.hitFlag = true;
        conflictPos.pos = polyInfo.Dim[0].HitPosition;
        MV1CollResultPolyDimTerminate(polyInfo);
        return  conflictPos;
    }
    return conflictPos;
}