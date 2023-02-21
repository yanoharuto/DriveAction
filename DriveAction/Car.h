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
#include "SoundPlayer.h"
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
	Car(VECTOR firstPos,VECTOR firstDir,VECTOR destinationPos,int duplicateModelHandle);
    virtual ~Car();
	/// <summary>
    /// 更新（移動処理）
    /// </summary>
	virtual void Update(const float deltaTime, const bool outsideHitFlag,ItemInfo itemInfo){};
	/// <summary>
	/// 衝突処理
	/// </summary>
	/// <param name="conflictInfo">ぶつかったかオブジェクトの情報</param>
	void ConflictProccess(float deltaTime, const ConflictExamineResultInfo conflictInfo);
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
	/// <summary>
	/// 今の速度
	/// </summary>
	/// <returns></returns>
	float GetTotalAccelPower();
	/// <summary>
	/// 自動運転
	/// </summary>
	/// <param name="deltaTime"></param>
	/// <param name="outsideHitFlag"></param>
	void AutoDrive(const float deltaTime, const bool outsideHitFlag, ItemInfo itemInfo);
	void CourceOutProccess(VECTOR lastCheckPos, VECTOR lastCheckDir);
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
	void ConflictReaction(float deltaTime, const ConflictExamineResultInfo conflictInfo);
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
	void PlayDriveSound(InputInfo inputDir);
	/// <summary>
	/// タイヤに渡す情報の初期化
	/// </summary>
	void InitWheelArgumentCarInfo();
	/// <summary>
	/// 落下
	/// </summary>
	/// <param name="deltaTime"></param>
	void Down(float deltaTime);

	//速さ
	float accelPower = 0;
	//外的要因による速さ
	float forcePower = 0;
	//ぶつかった時の跳ね返り力
	float conflictObjBouncePower;
	int brekeCount = 0;
	//ダメージを受けた時の操作不可能時間
	float damageReactionTime = -1.0f;
	//チェックポイントに当たってるか
	bool isGoalConflict = false;
	//地面に降りているか
	bool isOnGround = true;
	//ダメージ
	bool isDamage = false;
	//コースアウト処理中か
	bool isCourceOutProccessing = false;
	//タイヤ
	Wheels* wheels;
	//目的地
	VECTOR destinationPos = {};
	//コースアウトしたときの目的地
	VECTOR prevDestinationPos = {};
	//次の角度
	VECTOR destinationDir = {};
	//コースアウトしたときに向かなければいけない方向
	VECTOR prevDestinationDir = {};
	//ぶつかった物体との方向
	VECTOR conflictVec = {};
	//タイヤに渡したい情報
	WheelArgumentCarInfo wheelArgumentCarInfo = {};
};
