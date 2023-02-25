#include <math.h>
#include "CircuitTrack.h"
#include "CourceDataLoader.h"
#include "AssetManager.h"
#include "OriginalMath.h"

/// <summary>
/// ������
/// </summary>
/// <param name="player">�v���C���[�̕������</param>
/// <returns></returns>
CircuitTrack::CircuitTrack()
{
    nextGeneratePos = firstPos;
    //�h�ǂ̔��a
    radius = gurdRadius;
    tag = ObjectTag::stage;
    bouncePower = setBouncePower;
    courceModelHandle = AssetManager::GetDuplicate3DModelAssetHandle(stageFilePass + courceFilePass);
    obstracleModelHandle = AssetManager::GetDuplicate3DModelAssetHandle(stageFilePass + obstracleFilePass);
    floorModelHandle = AssetManager::GetDuplicate3DModelAssetHandle(stageFilePass + floorFilePass);
    MV1SetPosition(floorModelHandle, VGet(0, 0.0f, 0.0f));
}

/// <summary>
/// model�̉���@�R���W������������
/// </summary>
/// <returns></returns>
CircuitTrack::~CircuitTrack()
{
    MV1DeleteModel(courceModelHandle);
    MV1DeleteModel(obstracleModelHandle);
    MV1DeleteModel(floorModelHandle);
}
/// <summary>
/// �R�[�X�̊O���ɓ������Ă邩���ׂ�
/// </summary>
/// <param name="actor">�O���ɂ��邩���ׂ�������</param>
/// <returns>�R�[�X�̊O���ɂ���Ȃ�True</returns>
bool CircuitTrack::GetOutsideHitFlag(HitCheckExamineObjectInfo info)const
{
    return GetSphereConflictModelInfo(obstracleModelHandle, info).hitFlag;
}
bool CircuitTrack::HitCheckConflict(const HitCheckExamineObjectInfo examineObjInfo)
{
    return GetCourceConflictInfo(examineObjInfo).hitFlag;
}
/// <summary>
/// �R�[�X�̕ǂ�n�ʂɂԂ����Ă邩���ׂ�
/// </summary>
/// <param name="Actor">�Ԃ����Ă邩���ׂ�������</param>
/// <returns>�Ԃ����Ă���True</returns>
ConflictExamineResultInfo  CircuitTrack::GetCourceConflictInfo(HitCheckExamineObjectInfo info) const
{
    ConflictExamineResultInfo conflictInfo = GetSphereConflictModelInfo(obstracleModelHandle, info);
    //�������Ă鎞
    if (conflictInfo.hitFlag)
    {
        conflictInfo.radius = radius;
        conflictInfo.tag = tag;
        conflictInfo.bouncePower = bouncePower;
        return conflictInfo;
    }
    return { false,tag,{},radius };
}

/// <summary>
/// �R�[�X�̃��f����`��
/// </summary>
void CircuitTrack::Draw()
{
    MV1DrawModel(courceModelHandle);
    MV1DrawModel(obstracleModelHandle);
    MV1DrawModel(floorModelHandle);
}
void CircuitTrack::Update(VECTOR playerPos)
{
}
/// <summary>
/// MV1CollCheck_Sphere���g���ă��f���n���h�����˒��������ׂ��
/// </summary>
/// <param name="modelHandle">���ׂ郂�f��</param>
/// <param name="examineInfo">���ׂ邽�߂ɕK�v�ȏ��</param>
/// <returns>�Ԃ������ʒu��Ԃ���B�Ԃ����ĂȂ��Ȃ�HitFlag��false</returns>
ConflictExamineResultInfo CircuitTrack::GetSphereConflictModelInfo(int modelHandle,HitCheckExamineObjectInfo examineInfo) const
{
    DxLib::MV1_COLL_RESULT_POLY_DIM polyInfo = MV1CollCheck_Sphere(modelHandle, -1, examineInfo.pos, examineInfo.radius);
    ConflictExamineResultInfo conflictPos = {};
    if (polyInfo.HitNum != 0)
    {
        conflictPos.hitFlag = true;
        conflictPos.pos = polyInfo.Dim[0].HitPosition;
        MV1CollResultPolyDimTerminate(polyInfo);
        return  conflictPos;
    }
    return conflictPos;
}

