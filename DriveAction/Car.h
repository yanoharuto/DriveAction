#pragma once
#include "DxLib.h"
#include "Actor.h"
#include "Wheels.h"
#include "CarNeighborhoodExamineInfo.h"
#include "NeighborhoodInfo.h"
#include "SoundsGenerated.h"
/// <summary>
/// 車の加速とか減速とかするよ。どの向きに加速するかとかはwheelsからとってくるよ
/// </summary>
class Car :public Actor
{
public:
	Car();
	Car(VECTOR firstPos,VECTOR firstDir,VECTOR destinationPos,SoundPlayer* soundPlayer);
    virtual ~Car();
	/// <summary>
    /// 更新（移動処理）
    /// </summary>
	virtual void Update(const float deltaTime, const bool outsideHitFlag,NeighborhoodInfo neighInfo,SoundPlayer* soundPlayer){};
	/// <summary>
	/// 衝突処理
	/// </summary>
	/// <param name="conflictInfo">ぶつかったかオブジェクトの情報</param>
	void ConflictProcess(float deltaTime, const ConflictExamineResultInfo conflictInfo, SoundPlayer* soundPlayer);
	/// <summary>
	/// 描画
	/// </summary>
	virtual void Draw();
	/// <summary>
	/// 周辺を調べてもらうために渡す
	/// </summary>
	/// <returns></returns>
	CarNeighborhoodExamineInfo GetNeighExamineInfo();
	float GetAccelPower();
protected:

	/// <summary>
	/// 車がぶつかった時の関数
	/// </summary>
	/// <param name="conflictObjPos">ぶつかったオブジェクトの位置</param>
	/// <param name="conflictObjRad">ぶつかったオブジェクトの半径</param>
	void ConflictReaction(float deltaTime, const ConflictExamineResultInfo conflictInfo,SoundPlayer* soundPlayer);
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
	/// <summary>
	/// 自動運転
	/// </summary>
	/// <param name="deltaTime"></param>
	/// <param name="outsideHitFlag"></param>
	void AutoDrive(const float deltaTime, const bool outsideHitFlag,NeighborhoodInfo neighInfo, SoundPlayer* soundPlayer);
	/// <summary>
	/// 運転方向を返す
	/// </summary>
	/// <returns></returns>
	HandleDirection GetHandleDir();
	/// <summary>
	/// このフレームの間に進む量を出す
	/// </summary>
	/// <param name="handleDir">進行方向</param>
	/// <param name="outsideHitFlag">外側</param>
	/// <param name="deltaTime">経過時間</param>
	/// <returns>進む量</returns>
	VECTOR GetAccelVec(HandleDirection handleDir, bool outsideHitFlag, float deltaTime,SoundPlayer* soundPlayer);
	/// <summary>
	/// 周辺情報から曲がる情報に影響を与える
	/// </summary>
	/// <param name="neighInfo"></param>
	/// <returns></returns>
	float GetNeighSize(NeighborhoodInfo neighInfo);
	/// <summary>
	/// タイヤに渡す情報の初期化
	/// </summary>
	void InitWheelArgumentCarInfo();
	// 静的定数.
	const float accelSpeed = 12.4f;					// 通常の加速.
	const float maxSpeed = 200.0f;					// 最高速度.
	const float defaultDecel = 0.04f;			// なにもしない時の減速.
	const float breakDecel = 0.97f;				// ブレーキ時の減速.
	const float gripDecel = 0.125f;				// グリップの減速.
	const float gripPower = 0.06f;				// グリップ力.
	const float maxGripPower = 1.2f;	       	// 最大グリップ力.
	const float colideDecel = 0.2f;	             // 障害物にぶつかったときの減速率.
	const float outsideHitDecel = 0.4f;          //コースの外側に来た時の減速
	const float radiusValue = 3.0f;              //車の幅
	const float turnProccesLine = 9.0f;          //目的地に向かうときに曲がるか判断する
	const float examineRange = 150.0f;
	const float setBouncePower = 2.0;
	float accelPower = 0;                        //速さ
	float conflictObjBouncePower;
	int smokeEffectResource = -1;//煙のエフェクト
	int conflictEffectResource = -1;
	int accelerationEffectResource = -1;
	const std::string breakeSEAddress = "data/sound/brake.mp3";
	const std::string carClashSEAddress = "data/sound/carClash.mp3";
	const std::string carHornSEAddress = "data/sound/carHorn.mp3";
	const std::string drivingSEAddress = "data/sound/driving1.mp3";
	bool isStraightDash;//まっすぐ進んでいるかどうか
	Wheels* wheels;//タイヤ
	VECTOR destinationPos;//目的地
	VECTOR conflictVec;
	WheelArgumentCarInfo wheelArgumentCarInfo;//タイヤに渡したい情報

};

