#pragma once
#include "DxLib.h"
#include "Actor.h"

class Wheels;
/// <summary>
/// 車の加速とか減速とかするよ。どの向きに加速するかとかはwheelsからとってくるよ
/// </summary>
class Car :public Actor
{
public:
	Car();
    virtual ~Car();
	/// <summary>
    /// 更新（移動処理）
    /// </summary>
	virtual void Update(const float deltaTime, const bool outsideHitFlag) {};
	/// <summary>
	/// タイヤと車体の描画
	/// </summary>
	virtual void Draw();
protected:
	/// <summary>
	/// 進む方向と速さを更新する
	/// </summary>
	/// <param name="deltaTime">経過時間</param>
	/// <param name="accelVec">次の更新までに進む方向と速さ</param>
	void UpdateVelocity(const float deltaTime, const VECTOR accelVec);
	/// <summary>
	/// modelの描画場所を更新
	/// </summary>
	void UpdateMV1Pos();
	/// <summary>
	/// 車を回転させる
	/// </summary>
	void ModelSetMatrix();
	// 静的定数.
	const float accelSpeed = 1.8f;					// 通常の加速.
	const float maxSpeed = 180.0f;					// 最高速度.
	const float defaultDecel = -0.004f;			// なにもしない時の減速.
	const float breakDecel = -0.075f;				// ブレーキ時の減速.
	const float gripDecel = -0.025f;				// グリップの減速.
	const float gripPower = 1.2f;				// グリップ力.
	const float maxGripPower = 0.4f;				// 最大グリップ力.
	const float colideDecel = 0.4f;	    // 障害物にぶつかったときの減速率.
	const float outsideHitDecel = -0.08f;   //コースの外側に来た時の減速
	const float rage = static_cast<float>(DX_PI / 180.0f); //ラジアン
	const float radiusValue = 30.0f; //車の幅
	float accel = 0;             //計算結果によって出る速さ
	Wheels* wheels;//タイヤ
};

