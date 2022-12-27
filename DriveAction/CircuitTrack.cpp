#include "CircuitTrack.h"
#include "Player.h"

CircuitTrack::CircuitTrack(Player* player)
{
    modelHandle = MV1LoadModel("data/model/Circuit/Untitled.mv1");
    position = VGet(0, 0, 0);
    VECTOR scale = VGet(scaleValue, scaleValue, scaleValue);
    MV1SetScale(modelHandle, scale);
    tag = ObjectTag::stage;
    materialNum = 0;
    int playerRadius = static_cast<int>(player->GetRadius());
    playerRadius *= playerRadius;
    MV1SetupCollInfo(modelHandle, -1,32, 8 ,32);
}

CircuitTrack::~CircuitTrack()
{
    MV1DeleteModel(modelHandle);
}
/// <summary>
/// ステージのどのmaterialの上にいるか調べる
/// </summary>
/// <param name="object"></param>
void CircuitTrack::ConflictProcess(Actor* actor)
{
    
    
    printfDx("%f,%f\n", sY,eY);
    VECTOR startPos = actor->GetPos();
    VECTOR endPos = actor->GetPos();
    endPos.y = sY;
    startPos.y = eY;
    DxLib::MV1_COLL_RESULT_POLY polyInfo = MV1CollCheck_Line(modelHandle, -1, startPos, endPos);
    materialNum = polyInfo.MaterialIndex;
    if (polyInfo.HitFlag)
    {
        printfDx("%d,%d,%d,%d\n",polyInfo.FrameIndex ,materialNum, polyInfo.PolygonIndex,polyInfo.MeshIndex);
        printfDx("%f,%f,%f,%f\n",polyInfo.FrameIndex ,materialNum, polyInfo.PolygonIndex,polyInfo.MeshIndex);

    }
}
/// <summary>
/// コースのモデルを描画
/// </summary>
void CircuitTrack::Draw()
{
    MV1DrawModel(modelHandle);
}
