#include "Rock.h"
#include "AssetManager.h"
#include "ConflictManager.h"
//model�̃p�X
const std::string Rock::modelPass[] = { "Stage/LittleRock.mv1" ,"Stage/MiddleRock.mv1","Stage/BigRock.mv1" };
//�Ԃ��������ɕt����΂���
const int Rock::setBouncePower = 15.0f;
//�����蔻��̕�
const float Rock::setRadius[] = {65, 120.0f, 200};
/// <summary>
/// ��
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
/// �����蔻�������
/// </summary>
Rock::~Rock()
{
    ConflictManager::EraceConflictObjInfo(collider);
}

