#include "StageWall.h"
#include "AssetManager.h"
#include "ConflictManager.h"
/// <summary>
/// s“®”ÍˆÍ‚ğ‹·‚ß‚é•Ç
/// </summary>
StageWall::StageWall()
{
    modelHandle = AssetManager::Get3DModelAssetHandle(modelFilePass);
    tag = ObjectTag::stage;
    position = setFirstPos;
    wallCollider = new WallCollider(this, stageBiggestSize, stageSmallestSize);
    bouncePower = setBouncePower;
}

StageWall::~StageWall()
{
    ConflictManager::EraceConflictObjInfo(wallCollider);
}
