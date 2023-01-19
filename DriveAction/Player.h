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
	Player(VECTOR firstPos,VECTOR firstDir);
	///デストラクタ
    ~Player();
    /// <summary>
    /// 更新（移動処理）
    /// </summary>
	void Update(const float deltaTime, const bool outsideHitFlag, NeighborhoodInfo neighInfo) override;

private:
	/// <summary>
	/// 入力情報から進む向きと速さを所得
	/// </summary>
	/// <param name="inputKey">入力情報</param>
	/// <param name="outsideHitFlag">コースの外側にぶつかったかどうか</param>
	/// <returns>次の更新までに進む向きと速さ</returns>
	VECTOR GetAccelVec(const int inputKey,const bool outsideHitFlag,float deltaTime);
	void Init();
};

