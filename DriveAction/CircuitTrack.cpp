#include <math.h>
#include "CircuitTrack.h"
#include "CourceDataLoader.h"
#include "AssetManager.h"
#include "OriginalMath.h"
#include "Utility.h"
#include "ConflictManager.h"
/// <summary>
/// ������
/// </summary>
/// <param name="player">�v���C���[�̕������</param>
/// <returns></returns>
CircuitTrack::CircuitTrack()
{
    obstracleModelHandle = AssetManager::GetDuplicate3DModelAssetHandle(stageFilePass + obstracleFilePass);
    floorModelHandle = AssetManager::GetDuplicate3DModelAssetHandle(stageFilePass + floorFilePass);
    MV1SetPosition(obstracleModelHandle, outsideModelPosition);
    
    floorCollider = new MeshCollider(floorModelHandle, ObjectTag::stage);
    obstracleCollider = new MeshCollider(obstracleModelHandle, ObjectTag::obstacle);
}

/// <summary>
/// model�̉���@�R���W������������
/// </summary>
/// <returns></returns>
CircuitTrack::~CircuitTrack()
{
    ConflictManager::EraceConflictObjInfo(floorCollider);
    ConflictManager::EraceConflictObjInfo(obstracleCollider);
    SAFE_DELETE(floorCollider);
    SAFE_DELETE(obstracleCollider);
}


/// <summary>
/// �R�[�X�̃��f����`��
/// </summary>
void CircuitTrack::Draw()
{
    MV1DrawModel(obstracleModelHandle);
    MV1DrawModel(floorModelHandle);
}