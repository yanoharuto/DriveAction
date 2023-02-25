#include <math.h>
#include "CircuitTrack.h"
#include "CourceDataLoader.h"
#include "AssetManager.h"
#include "OriginalMath.h"

/// <summary>
/// 初期化
/// </summary>
/// <param name="player">プレイヤーの幅を取る</param>
/// <returns></returns>
CircuitTrack::CircuitTrack()
{
    nextGeneratePos = firstPos;
    //防壁の半径
    radius = gurdRadius;
    tag = ObjectTag::stage;
    bouncePower = setBouncePower;
    courceModelHandle = AssetManager::GetDuplicate3DModelAssetHandle(stageFilePass + courceFilePass);
    obstracleModelHandle = AssetManager::GetDuplicate3DModelAssetHandle(stageFilePass + obstracleFilePass);
    floorModelHandle = AssetManager::GetDuplicate3DModelAssetHandle(stageFilePass + floorFilePass);
    MV1SetPosition(floorModelHandle, VGet(0, 0.0f, 0.0f));
}

/// <summary>
/// modelの解放　コリジョンも消える
/// </summary>
/// <returns></returns>
CircuitTrack::~CircuitTrack()
{
    MV1DeleteModel(courceModelHandle);
    MV1DeleteModel(obstracleModelHandle);
    MV1DeleteModel(floorModelHandle);
}
/// <summary>
/// コースの外側に当たってるか調べる
/// </summary>
/// <param name="actor">外側にいるか調べたいもの</param>
/// <returns>コースの外側にいるならTrue</returns>
bool CircuitTrack::GetOutsideHitFlag(HitCheckExamineObjectInfo info)const
{
    return GetSphereConflictModelInfo(obstracleModelHandle, info).hitFlag;
}
bool CircuitTrack::HitCheckConflict(const HitCheckExamineObjectInfo examineObjInfo)
{
    return GetCourceConflictInfo(examineObjInfo).hitFlag;
}
/// <summary>
/// コースの壁や地面にぶつかってるか調べる
/// </summary>
/// <param name="Actor">ぶつかってるか調べたいもの</param>
/// <returns>ぶつかってたらTrue</returns>
ConflictExamineResultInfo  CircuitTrack::GetCourceConflictInfo(HitCheckExamineObjectInfo info) const
{
    ConflictExamineResultInfo conflictInfo = GetSphereConflictModelInfo(obstracleModelHandle, info);
    //当たってる時
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
/// コースのモデルを描画
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
/// MV1CollCheck_Sphereを使ってモデルハンドルが射程内か調べるよ
/// </summary>
/// <param name="modelHandle">調べるモデル</param>
/// <param name="examineInfo">調べるために必要な情報</param>
/// <returns>ぶつかった位置を返すよ。ぶつかってないならHitFlagはfalse</returns>
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

