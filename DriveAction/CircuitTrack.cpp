#include <math.h>
#include "CircuitTrack.h"
#include "CourceDataLoader.h"
#include "AssetManager.h"
#include "OriginalMath.h"
#include "Utility.h"
#include "ConflictManager.h"
#include "GetGeneratePos.h"
/// <summary>
/// 初期化
/// </summary>
/// <returns></returns>
CircuitTrack::CircuitTrack()
{
    floorModelHandle = AssetManager::Get3DModelAssetHandle(stageFilePass + floorFilePass);
    for (int i = 0; i < RockPattern; i++)
    {
        std::vector<VECTOR> posList = GetGeneratePos::CSVConvertPosition("data/stageMap_rockPos.csv",i);
        for (auto ite = posList.begin(); ite != posList.end(); ite++)
        {
            VECTOR pos = (*ite);
            pos.y = rockYPos * i;
            Rock* rock = new Rock(pos,i);
            rocks.push_back(rock);
        }
    }

    stageWall = new StageWall();
}

/// <summary>
/// modelの解放　コリジョンも消える
/// </summary>
/// <returns></returns>
CircuitTrack::~CircuitTrack()
{
    for (auto ite = rocks.begin(); ite != rocks.end(); ite++)
    {
        SAFE_DELETE((*ite));
    }
    SAFE_DELETE(stageWall);
}


/// <summary>
/// コースのモデルを描画
/// </summary>
void CircuitTrack::Draw()
{
    for (auto ite = rocks.begin(); ite != rocks.end(); ite++)
    {
        (*ite)->Draw();
    }
    stageWall->Draw();
    MV1DrawModel(floorModelHandle);
}