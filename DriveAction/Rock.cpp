#include "Rock.h"
#include "AssetManager.h"
#include "ConflictManager.h"
//model‚ÌƒpƒX
const std::string Rock::modelPass[] = { "Stage/LittleRock.mv1" ,"Stage/MiddleRock.mv1","Stage/BigRock.mv1" };
//‚Ô‚Â‚©‚Á‚½‚É•t‚«”ò‚Î‚·—Í
const int Rock::setBouncePower = 15.0f;
//“–‚½‚è”»’è‚Ì•
const float Rock::setRadius[] = {65, 120.0f, 200};
/// <summary>
/// Šâ
/// </summary>
/// <param name="setPos"></param>
/// <param name="pattern"></param>
Rock::Rock(VECTOR setPos, int pattern)
{
    modelHandle = AssetManager::Get3DModelAssetHandle(modelPass[pattern]);
    position = setPos;
    radius = setRadius[pattern];
    collider = new SphereCollider(this);
    tag = ObjectTag::obstacle;
    bouncePower = setBouncePower;
}
/// <summary>
/// “–‚½‚è”»’è‚ğÁ‚·
/// </summary>
Rock::~Rock()
{
    ConflictManager::EraceConflictObjInfo(collider);
}

