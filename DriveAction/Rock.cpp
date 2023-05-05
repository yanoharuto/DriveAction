#include "Rock.h"
#include "AssetManager.h"
#include "ConflictManager.h"
Init::InitObjKind Rock::rockPattern[RockPattern] = { Init::littleRock,Init::middleRock,Init::bigRock };
/// <summary>
/// 岩
/// </summary>
/// <param name="setPos"></param>
/// <param name="pattern"></param>
Rock::Rock(VECTOR setPos, int pattern)
    :Actor(rockPattern[pattern])
{
    setPos.y = position.y;
    position = setPos;
    collider = new SphereCollider(this);
    tag = ObjectTag::obstacle;
}
/// <summary>
/// 当たり判定を消す
/// </summary>
Rock::~Rock()
{
    ConflictManager::EraceConflictObjInfo(collider);
}

