#pragma once
#include "Item.h"
#include "CpuCarMode.h"
#include "DxLib.h"
#include "Actor.h"
#include "Wheels.h"
#include "CarNeighborhoodExamineInfo.h"
#include "NeighborhoodInfo.h"
#include "InputDirection.h"
#include "ItemInfo.h"
/// <summary>
/// 車の加速とか減速とかするよ。どの向きに加速するかとかはwheelsからとってくるよ
/// </summary>
class Car abstract :public Actor
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
	virtual void Update(const float deltaTime, const bool outsideHitFlag,ItemInfo itemInfo,SoundPlayer* soundPlayer){};
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
	/// アイテムに渡したい情報を出す
	/// </summary>
	/// <returns></returns>
	ItemArgumentCarInfo GetItemArgumentInfo();
	/// <summary>
	/// 今の速度は最大速度の何割なのか所得出来る
	/// </summary>
	/// <returns></returns>
	float GetTotalAccelPowerPercent();
protected:
	/// <summary>
	/// アイテムの効果を受け取る
	/// </summary>
	/// <param name="item"></param>
	/// <param name="deltaTime"></param>
	void RecieveItemEffecacy(ItemInfo itemInfo, float deltaTime);
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
	void DamageReaction(float deltaTime);
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
	void AutoDrive(const float deltaTime, const bool outsideHitFlag ,ItemInfo itemInfo,SoundPlayer* soundPlayer);
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
	/// タイヤに渡す情報の初期化
	/// </summary>
	void InitWheelArgumentCarInfo();
	void Down(float deltaTime);
	//チェックポイントに通過した回数
	int checkCount = 0;
	// 通常の加速.
	const float accelAddSpeed = 38.4f;					
	// 通常最高速度.
	const float maxAccelSpeed = 230.0f;					
	//外的要因の速さの最高速度
	const float maxAddForcePower = 100.0f;
	//外的要因の速さ
	const float addAccelForce = 8.0f;
	//これ以下の速度になってたらaccelPowerを0にするよ
	const float stopAccelLine = 5.0f;
	// なにもしない時の減速.
	const float defaultDecel = 0.2f;			
	// ブレーキ時の減速.
	const float breakDecel = 0.97f;				
	// グリップの減速.
	const float gripDecel = 0.54f;				
	// グリップ力.
	const float gripPower = 0.14f;				
	// 障害物にぶつかったときの減速率.
	const float colideDecel = 0.2f;	  
	//コースの外側に来た時の減速
	const float outsideHitDecel = 0.28f;          
	//車の幅
	const float radiusValue = 3.8f;              
	//目的地に向かうときに曲がるか判断する
	const float turnProccesAngularLine = 5.0f;  
	//跳ね返り力の固定値
	const float setBouncePower = 1.0f;
	//降りる速度
	const float downSpeed = 10.8f;
	//最初のY座標
	const float firstPosY = -4.0;
	//速さ
	float accelPower = 0;                        
	//外的要因による速さ
	float forcePower = 0;
	//ぶつかった時の跳ね返り力
	float conflictObjBouncePower;
	//ダメージを受けた時の操作不可能時間
	float damageReactionTime = -1.0f;
	//ダメージを受けた時の操作不可能時間の合計
	const float setDamageReactionTime = 1.2f;
	//煙のエフェクト
	int smokeEffectResource = -1;
	//ぶつかった時のエフェクト
	int conflictEffectResource = -1;
	//外的要因で早くなった時のエフェクト
	int accelerationEffectResource = -1;
	int accelerationPlayEffect = -1;
	int count = 0;
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
	//地面に降りているか
	bool isOnGround;
	bool isDamage;

	//タイヤ
	Wheels* wheels;
	VECTOR itemEffecacyValue = {};
	//目的地
	VECTOR destinationPos;
	//次の角度
	VECTOR destinationDir;
	//ぶつかった物体との方向
	VECTOR conflictVec;
	//タイヤに渡したい情報
	WheelArgumentCarInfo wheelArgumentCarInfo;
};

