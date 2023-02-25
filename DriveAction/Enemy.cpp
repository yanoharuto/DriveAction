#include "Enemy.h"

Enemy::Enemy(VECTOR firstPos, VECTOR firstDir, VECTOR destinationPos, int duplicateModelHandle)
{
    MV1SetScale(modelHandle, {scale,scale,scale});
}

Enemy::~Enemy()
{
}

void Enemy::Update(const float deltaTime, VECTOR playerPos, ItemInfo itemInfo)
{
}

void Enemy::Draw()
{
    MV1DrawModel(modelHandle);
}
