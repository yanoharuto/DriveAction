#include "CircuitTrack.h"
#include <math.h>
/// <summary>
/// 初期化
/// </summary>
/// <param name="player">プレイヤーの幅を取る</param>
/// <returns></returns>
CircuitTrack::CircuitTrack(std::string courceModelAdress, std::string outsideModelAdress)
{
    courceModelHandle = MV1LoadModel(courceModelAdress.c_str());
    outsideModelHandle = MV1LoadModel(outsideModelAdress.c_str());
    MV1SetPosition(outsideModelHandle, outsideModelPosition);    //若干コースの外側を下げる
    //大きさ変更
    VECTOR scale = VGet(courceModelScaleValue, courceModelScaleValue, courceModelScaleValue);
    MV1SetScale(courceModelHandle, scale);
    scale = VGet(outsideModelScaleValue, outsideModelScaleValue, outsideModelScaleValue);
    MV1SetScale(outsideModelHandle, scale);
    //防壁の半径
    radius = gurdRadius;
    tag = ObjectTag::stage;
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
bool CircuitTrack::GetOutsideHitFlag(ConflictProccessArgumentInfo info)const
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
/// <summary>
/// コースの壁にぶつかってるか調べる
/// </summary>
/// <param name="Actor">ぶつかってるか調べたいもの</param>
/// <returns>ぶつかってたらTrue</returns>
ConflictProccessArgumentInfo  CircuitTrack::GetCourceConflictInfo(ConflictProccessArgumentInfo info) const
{
    //
    CarNeighborhoodExamineInfo examineInfo = { info.pos,info.radius };
    ConflictProccessArgumentInfo conflictInfo = GetSphereConflictModelInfo(courceModelHandle, examineInfo);
    //当たってる時
    if (conflictInfo.hitFlag)
    {
        conflictInfo.radius = radius;
        conflictInfo.tag = tag;
        return conflictInfo;
    }
  
    return { false,tag,{},radius };
}

/// <summary>
/// 引数の範囲に何かあるか調べるよ
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