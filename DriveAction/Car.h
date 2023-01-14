#pragma once
#include "DxLib.h"
#include "Actor.h"
#include "Wheels.h"
/// <summary>
/// 車の加速とか減速とかするよ。どの向きに加速するかとかはwheelsからとってくるよ
/// </summary>
class Car :public Actor
{
public:
	Car();
	Car(VECTOR firstPos,VECTOR firstDir);
    virtual ~Car();
	/// <summary>
    /// 更新（移動処理）
    /// </summary>
	virtual void Update(const float deltaTime, const bool outsideHitFlag) {};
	/// <summary>
	/// 衝突処理
	/// </summary>
	/// <param name="conflictInfo">ぶつかったかオブジェクトの情報</param>
	void ConflictProcess(const ArgumentConflictInfo conflictInfo) override;
	/// <summary>
	/// 描画
	/// </summary>
	virtual void Draw();
protected:
	/// <summary>
	/// 車がぶつかった時の関数
	/// </summary>
	/// <param name="conflictObjPos">ぶつかったオブジェクトの位置</param>
	/// <param name="conflictObjRad">ぶつかったオブジェクトの半径</param>
	void ConflictReaction(const VECTOR conflictObjPos, const float conflictObjRad);
	/// <summary>
	/// 車が攻撃を受けたら関数
	/// </summary>
	/// <param name="conflictObjPos">ぶつかったオブジェクトの位置</param>
	/// <param name="conflictObjRad">ぶつかったオブジェクトの半径</param>
	void DamageReaction(const VECTOR conflictObjPos, const float conflictObjRad);
	/// <summary>
	/// 進む方向と速さを更新する
	/// </summary>
	/// <param name"deltaTime">経過時間</param>
	/// <param name="accelVec">次の更新までに進む方向と速さ</param>
	void UpdateVelocity(const VECTOR accelVec);
	/// <summary>
	/// modelの描画場所を更新
	/// </summary>
	void UpdateMV1Pos();
	/// <summary>
	/// 車を回転させる
	/// </summary>
	void ModelSetMatrix();
	void AutoDrive(const float deltaTime, const bool outsideHitFlag);
	HandleDirection GetHandleDir();
	virtual VECTOR GetAccelVec(HandleDirection handleDir, bool outsideHitFlag, float deltaTime);
	// 静的定数.
	const float accelSpeed = 0.28f;					// 通常の加速.
	const float maxSpeed = 16.0f;					// 最高速度.
	const float defaultDecel = 0.04f;			// なにもしない時の減速.
	const float breakDecel = 0.075f;				// ブレーキ時の減速.
	const float gripDecel = 0.125f;				// グリップの減速.
	const float gripPower = 0.02f;				// グリップ力.
	const float maxGripPower = 0.4f;				// 最大グリップ力.
	const float colideDecel = 0.45f;	    // 障害物にぶつかったときの減速率.
	const float outsideHitDecel = 0.2f;   //コースの外側に来た時の減速
	const float rage = static_cast<float>(DX_PI / 180.0f); //ラジアン
	const float radiusValue = 3.0f; //車の幅
	float accelPower = 0;             //計算結果によって出る速さ
	const float turnProccesLine = 7.0f;//目的地に向かうときに曲がるか判断する
	Wheels* wheels;//タイヤ
	VECTOR destinationPos;
};

