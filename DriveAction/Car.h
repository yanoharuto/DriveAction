#pragma once
#include "CpuCarMode.h"
#include "DxLib.h"
#include "Actor.h"
#include "Wheels.h"
#include "CarNeighborhoodExamineInfo.h"
#include "NeighborhoodInfo.h"
#include "SoundsGenerated.h"
#include "InputDirection.h"
/// <summary>
/// 車の加速とか減速とかするよ。どの向きに加速するかとかはwheelsからとってくるよ
/// </summary>
class Car :public Actor
{

public:
	Car();
	/// <summary>
	/// 初期位置や方角とか
	/// </summary>
	/// <param name="firstPos"></param>
	/// <param name="firstDir"></param>
	/// <param name="destinationPos"></param>
	/// <param name="soundPlayer"></param>
	Car(VECTOR firstPos,VECTOR firstDir,VECTOR destinationPos,SoundPlayer* soundPlayer);
    virtual ~Car();
	/// <summary>
    /// 更新（移動処理）
    /// </summary>
	virtual void Update(const float deltaTime, const bool outsideHitFlag,VECTOR pos,SoundPlayer* soundPlayer){};
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
	/// <summary>
	/// 今の速度は最大速度の何割なのか所得出来る
	/// </summary>
	/// <returns></returns>
	float GetAccelPowerPercent();
protected:
	/// <summary>
	/// 爆弾攻撃
	/// </summary>
	void BombAttack();
	/// <summary>
	/// 飛ぶ
	/// </summary>
	/// <param name="deltaTime"></param>
	void Fly(float deltaTime);
	/// <summary>
	/// 落ちる
	/// </summary>
	/// <param name="deltaTime"></param>
	void Down(float deltaTime);
	/// <summary>
	/// 空を飛んでる時の処理
	/// </summary>
	/// <param name="deltaTime"></param>
	void FlyUpdate(float deltaTime);

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
	void AutoDrive(const float deltaTime, const bool outsideHitFlag , VECTOR pos ,SoundPlayer* soundPlayer);
	/// <summary>
	/// 運転方向を返す
	/// </summary>
	/// <returns></returns>
	InputInfo GetAutoDriveDirection();
	/// <summary>
	/// このフレームの間に進む量を出す
	/// </summary>
	/// <param name="handleDir">入力された方向</param>
	/// <param name="outsideHitFlag">コースの外にいるか</param>
	/// <param name="deltaTime">経過時間</param>
	/// <param name="soundPlayer">音を出すやつ</param>
	/// <returns>進む量</returns>
	VECTOR GetAccelVec(InputInfo inputDir, bool outsideHitFlag, float deltaTime);
	/// <summary>
	/// 運転中になる音を再生する
	/// </summary>
	/// <param name="inputDir"></param>
	/// <param name="soundPlayer"></param>
	void PlayDriveSound(InputInfo inputDir, SoundPlayer* soundPlayer);
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
	//チェックポイントに通過した回数
	int checkCount = 0;
	// 通常の加速.
	const float accelAddSpeed = 18.4f;					
	// 通常最高速度.
	const float maxAccelSpeed = 200.0f;					
	//外的要因の速さの最高速度
	const float maxAddSpeed = 50.0f;
	//外的要因の速さ
	const float addAccelSpeed = 5.0f;
	//これ以下の速度になってたらaccelPowerを0にするよ
	const float stopAccelLine = 0.03f;
	// なにもしない時の減速.
	const float defaultDecel = 0.04f;			
	// ブレーキ時の減速.
	const float breakDecel = 0.97f;				
	// グリップの減速.
	const float gripDecel = 0.34f;				
	// グリップ力.
	const float gripPower = 0.036f;				
	// 障害物にぶつかったときの減速率.
	const float colideDecel = 0.2f;	  
	//コースの外側に来た時の減速
	const float outsideHitDecel = 0.4f;          
	//車の幅
	const float radiusValue = 3.0f;              
	//目的地に向かうときに曲がるか判断する
	const float turnProccesAngularLine = 3.0f;  
	//跳ね返り力の固定値
	const float setBouncePower = 1.0f;
	//周辺調査範囲
	const float examineRange = 150.0f;
	
	//速さ
	float accelPower = 0;                        
	//外的要因で早くなると増える
	float addForcePower = 0;
	//ぶつかった時の跳ね返り力
	float conflictObjBouncePower;
	//空を飛ぶ時用
	float flyY = 0;
	//煙のエフェクト
	int smokeEffectResource = -1;
	//ぶつかった時のエフェクト
	int conflictEffectResource = -1;
	//外的要因で早くなった時のエフェクト
	int accelerationEffectResource = -1;
	//止まった時の効果音
	const std::string breakeSEAddress = "data/sound/brake.mp3";
	//ぶつかった時の効果音
	const std::string carClashSEAddress = "data/sound/carClash.mp3";
	//クラクションの効果音
	const std::string carHornSEAddress = "data/sound/carHorn.mp3";
	//運転中の効果音
	const std::string drivingSEAddress = "data/sound/driving1.mp3";
	//チェックポイントに当たってるか
	bool isGoalConflict;

	float firstPosY = 0;
	float bombAttackTime = 0;
	const float bombCoolTime = 5;
	const float coolTime = 45.0f;
	const float flyPower = 0.6f;
	const float downSpeed = 0.37f;
	const float maxHeight = 1.0f;
	const float maxFlyTime = 15.0f;
	CarMode carMode = CarMode::normal;
	float flyTime = 0;

	//タイヤ
	Wheels* wheels;
	//目的地
	VECTOR destinationPos;
	//次の角度
	VECTOR destinationDir;
	//ぶつかった物体との方向
	VECTOR conflictVec;
	//タイヤに渡したい情報
	WheelArgumentCarInfo wheelArgumentCarInfo;
};

