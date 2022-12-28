#include "CircuitTrack.h"
#include "Player.h"
/// <summary>
/// 初期化
/// </summary>
/// <param name="player">プレイヤーの幅を取る</param>
/// <returns></returns>
CircuitTrack::CircuitTrack(Player* player)
{
    courceModelHandle = MV1LoadModel("data/model/Circuit/CircuitCource.mv1");
    outsideModelHandle = MV1LoadModel("data/model/Circuit/CircuitOutside.mv1");
    //若干コースの外側を下げる
    MV1SetPosition(outsideModelHandle, outsideModelPosition);

    VECTOR scale = VGet(courceModeScaleValue, courceModeScaleValue, courceModeScaleValue);
    MV1SetScale(courceModelHandle, scale);
    scale = VGet(outsideModelScaleValue, outsideModelScaleValue, outsideModelScaleValue);
    MV1SetScale(outsideModelHandle, scale);

    tag = ObjectTag::stage;
    int playerRadius = static_cast<int>(player->GetRadius());
    playerRadius *= playerRadius;
    //コリジョンを作る
    MV1SetupCollInfo(outsideModelHandle, -1,playerRadius, setupYDivNum ,playerRadius,-1);
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
bool CircuitTrack::GetOutsideHitFlag(Actor* actor)
{
    //線分の始まりと終わりを作る
    //ｘとｚ座標を取ってくる
    VECTOR startPos = actor->GetPos();
    startPos.y = sY;
    VECTOR endPos = startPos;
    endPos.y = eY;
    //外側にいるか調べる
    DxLib::MV1_COLL_RESULT_POLY polyInfo = MV1CollCheck_Line(outsideModelHandle, -1, startPos, endPos);
    return polyInfo.HitFlag;
}

/// <summary>
/// コースのモデルを描画
/// </summary>
void CircuitTrack::Draw()
{
    MV1DrawModel(courceModelHandle);
    MV1DrawModel(outsideModelHandle);
}
