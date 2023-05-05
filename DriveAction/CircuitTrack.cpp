#include <math.h>
#include "CircuitTrack.h"
#include "CourceDataLoader.h"
#include "AssetManager.h"
#include "OriginalMath.h"
#include "Utility.h"
#include "ConflictManager.h"
#include "GetGeneratePos.h"
#include "InitActor.h"
/// <summary>
/// 初期化
/// </summary>
/// <returns></returns>
CircuitTrack::CircuitTrack()
{
    InitActor* init = new InitActor();
    ActorParametor initParam = init->GetActorParametor(Init::stageFloor);
    floorModelHandle = AssetManager::Get3DModelAssetHandle(initParam.modelPass);
    for (int i = 0; i < RockPattern; i++)
    {
        std::vector<VECTOR> posList = GetGeneratePos::CSVConvertPosition("data/stageMap_rockPos.csv",i);
        for (auto ite = posList.begin(); ite != posList.end(); ite++)
        {
            Rock* rock = new Rock((*ite), i);
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