#pragma once
#include "Car.h"
#include "AssetManager.h"
#include "SphereCollider.h"
class Wheels;
 /// <summary>
 /// プレイヤー(車)
 /// </summary>
 class PlayerCar final: public Car
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <returns></returns>
	PlayerCar();
	PlayerCar(VECTOR firstPos);
	///デストラクタ
    ~PlayerCar();
    /// <summary>
    /// 更新（移動処理）
    /// </summary>
	void Update(const float deltaTime, VECTOR destinationPos,ItemInfo itemInfo) override;
private:
	void PostDamageProccess(float deltaTime)override;
	void DamageReaction(const ConflictExamineResultInfo conflictInfo)override;
	//入力に酔って走る方向を変える
	void SetInputDir();
	//高さ
	const float setFirstPosY = 6.0f;
	const float setDamageCoolTime = 3.0f;
	int damageEffect[3] = { -1,-1,-1 };
	//体力
	int HP = 0;
	float damageCoolTime = -1.0f;
	SphereCollider* collider;
};