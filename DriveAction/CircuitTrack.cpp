#include <math.h>
#include "CircuitTrack.h"
#include "CourceDataLoader.h"
#include "AssetManager.h"
#include "OriginalMath.h"
#include "Utility.h"
#include "ConflictManager.h"
/// <summary>
/// 初期化
/// </summary>
/// <param name="player">プレイヤーの幅を取る</param>
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
/// modelの解放　コリジョンも消える
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
/// コースのモデルを描画
/// </summary>
void CircuitTrack::Draw()
{
    MV1DrawModel(obstracleModelHandle);
    MV1DrawModel(floorModelHandle);
}