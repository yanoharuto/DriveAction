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
	///デストラクタ
    ~Player();
    /// <summary>
    /// 更新（移動処理）
    /// </summary>
    void Update(const float deltaTime,const bool outsideHitFlag) override;
    /// <summary>
    /// 描画
    /// </summary>
    void Draw() override;
private:
	/// <summary>
	/// 入力情報から進む向きと速さを所得
	/// </summary>
	/// <param name="inputKey">入力情報</param>
	/// <param name="outsideHitFlag">コースの外側にぶつかったかどうか</param>
	/// <returns>次の更新までに進む向きと速さ</returns>
	VECTOR GetAccelVec(const int inputKey,const bool outsideHitFlag);
	//todo コンストラクタで引数で変更できるようにする
	VECTOR firstPos = { -300.0f,-0.0f,-83.0f };//レース開始位置
	VECTOR firstDir = { -0.9f,0,-0.02f };//初期向き
};

