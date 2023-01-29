#pragma once
#include "Car.h"
class Wheels;
 /// <summary>
 /// プレイヤー(車)
 /// </summary>
 class Player final: public Car
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <returns></returns>
	Player();
	Player(VECTOR firstPos,VECTOR firstDir,VECTOR destinationPos,SoundPlayer* soundPlayer);
	///デストラクタ
    ~Player();
    /// <summary>
    /// 更新（移動処理）
    /// </summary>
	void Update(const float deltaTime, const bool outsideHitFlag, NeighborhoodInfo neighInfo,SoundPlayer* soundPlayer) override;

private:
	void Init();

};

