#include "CircuitTrack.h"
#include "Car.h"
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
bool CircuitTrack::GetOutsideHitFlag(Car* car)const
{
    //線分の始まりと終わりを作る
    //ｘとｚ座標を取ってくる
    VECTOR startPos = car->GetPos();
    startPos.y = sY;
    VECTOR endPos = startPos;
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
ArgumentConflictInfo  CircuitTrack::GetCourceConflictInfo(Car* car) const
{
    //壁にぶつかったか関数にかける
    MV1_COLL_RESULT_POLY_DIM polyInfo;
    polyInfo = MV1CollCheck_Sphere(courceModelHandle, -1, car->GetPos(),car->GetRadius());

    //当たってる時は当たった場所を返す
    if (polyInfo.HitNum != 0)
    {
        VECTOR hitPos = polyInfo.Dim->HitPosition;
        MV1CollResultPolyDimTerminate(polyInfo);
        return { true,tag,hitPos,radius };
    }
  
    return {};
}

/// <summary>
/// コースのモデルを描画
/// </summary>
void CircuitTrack::Draw()
{
  MV1DrawModel(courceModelHandle);
  MV1DrawModel(outsideModelHandle);
}
