#include <math.h>
#include "CircuitTrack.h"
#include "CourceDataLoader.h"
#include "AssetManager.h"
/// <summary>
/// 初期化
/// </summary>
/// <param name="player">プレイヤーの幅を取る</param>
/// <returns></returns>
CircuitTrack::CircuitTrack()
{
    std::string genericAddress = CourceDataLoader::GetStageDataGenericAddress();
    courceModelHandle = AssetManager::Get3DModelAssetHandle(genericAddress + courceAddress);
    outsideModelHandle = AssetManager::Get3DModelAssetHandle(genericAddress + outsideAddress);
    MV1SetPosition(outsideModelHandle, outsideModelPosition);    //若干コースの外側を下げる
    //大きさ変更
    VECTOR scale = VGet(courceModelScaleValue, courceModelScaleValue, courceModelScaleValue);
    MV1SetScale(courceModelHandle, scale);
    scale = VGet(outsideModelScaleValue, outsideModelScaleValue, outsideModelScaleValue);
    MV1SetScale(outsideModelHandle, scale);
    //防壁の半径
    radius = gurdRadius;
    tag = ObjectTag::stage;
    bouncePower = setBouncePower;
}

/// <summary>
/// modelの解放　コリジョンも消える
/// </summary>
/// <returns></returns>
CircuitTrack::~CircuitTrack()
{
    MV1DeleteModel(courceModelHandle);
    MV1DeleteModel(outsideModelHandle);
}
/// <summary>
/// コースの外側に当たってるか調べる
/// </summary>
/// <param name="actor">外側にいるか調べたいもの</param>
/// <returns>コースの外側にいるならTrue</returns>
bool CircuitTrack::GetOutsideHitFlag(HitCheckExamineObjectInfo info)const
{
    //線分の始まりと終わりを作る
    //ｘとｚ座標を取ってくる
    VECTOR startPos = info.pos;
    startPos.y = sY;
    VECTOR endPos = info.pos;
    endPos.y = eY;
    //外側にいるか調べる
    DxLib::MV1_COLL_RESULT_POLY polyInfo = MV1CollCheck_Line(outsideModelHandle, -1, startPos, endPos);
    return polyInfo.HitFlag;
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
    ConflictExamineResultInfo conflictInfo = GetSphereConflictModelInfo(courceModelHandle,info);
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
/// 引数の範囲に何かあるか調べるよ
/// </summary>
/// <param name="examineInfo"></param>
/// <returns></returns>
NeighborhoodInfo CircuitTrack::GetOutsideExamineInfo(HitCheckExamineObjectInfo examineInfo) const
{
    NeighborhoodInfo returnValueInfo;
    returnValueInfo.outside = GetSphereConflictModelInfo(outsideModelHandle,examineInfo);
    HitCheckExamineObjectInfo examineInfo2 = examineInfo;
    examineInfo2.pos.y = outsideModelPosition.y;
    returnValueInfo.obstacle = GetSphereConflictModelInfo(courceModelHandle, examineInfo2);
    return returnValueInfo;
}

/// <summary>
/// コースのモデルを描画
/// </summary>
void CircuitTrack::Draw()
{
    MV1DrawModel(courceModelHandle);
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