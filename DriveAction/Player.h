#pragma once
#include "Actor.h"
struct Wheel
{
	int modelHandle = -1;
	VECTOR betweenBody = {};
	VECTOR direction = {};
	MATRIX matrix = {};
};
enum WheelDirection
{
	left,
	right,
	normal
};
 /// <summary>
 /// プレイヤー(車)
 /// </summary>
 class Player final: public Actor
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
    void Update(const float deltaTime) override;
    /// <summary>
    /// 描画
    /// </summary>
    void Draw() override;
private:
	/// <summary>
	/// タイヤの初期化
	/// </summary>
	/// <param name="_Wheele">初期化したいタイヤ</param>
	/// <param name="_ModelHandle">タイヤのモデル</param>
	/// <param name="_Pos">車から見た位置</param>
	/// <param name="_Rota">回転角</param>
	void InitWheele(Wheel& wheele,int modelHandle, VECTOR pos, float _rota);
	/// <summary>
	/// 左右キーを入力したら傾け、上下キーで回転させる
	/// </summary>
	/// <param name="_Key">入力情報</param>
	void WheelUpdate(const int key);
	/// <summary>
	/// タイヤの位置を車に合わせる
	/// </summary>
	/// <param name="_wheel"></param>
	VECTOR WheelGetPos(const Wheel& wheel);
	/// <summary>
	/// タイヤの位置と回転を設定
	/// </summary>
	/// <param name="_wheel">設定したいタイヤ</param>
	/// <param name="_rotaX">タイヤの転がるときの回転</param>
	/// <param name="_rotaY">タイヤの向きがずれるときの回転</param>
	void SetWheelMatrix(Wheel& wheel,const float rotaX,const float rotaY);

	float GetCircleRadius(float firstWheelRota);
	// 静的定数.
	static const float ACCEL;					// 通常の加速.
	static const float MAX_SPEED;				// 最高速度.
	static const float DEFAULT_DECEL;			// なにもしない時の減速.
	static const float BREAK_DECEL;				// ブレーキ時の減速.
	static const float GRIP_DECEL;				// グリップの減速.
	static const float GRIP_POWER;				// グリップ力.
	static const float MAX_GRIP_POWER;				// 最大グリップ力.
	static const float COLIDE_DECEL_FAC;	    // 障害物にぶつかったときの減速率.
	const float firstLWheeleRota = 0.0f;		//左側タイヤの初期角度
	const float firstRWheeleRota = 180.0f;		//右側タイヤの初期角度
	const float wheeleDriveRotaSpeed = 200.0f;
	const float wheelCurvePower = 1.7f;
	const float maxWheelRota = 45.5f;
	const float rotaCalculationLine = 1.2f;
	WheelDirection wheelDir;
	float accel = 0;
	float wheelDriveSpeed = 0.0f;
	float wheelDriveRota = 0.0f;

	int wheeleModelHandle;
	Wheel lFWheel;
	Wheel lBWheel;
	Wheel rFWheel;
	Wheel rBWheel;
	const VECTOR fWheelPos = {2.7f,-0.8f,1.6f};
	const VECTOR bWheelPos = {2.4f,-0.8f,1.6f};
	const VECTOR firstPos = { -300.0f,-4.8f,-83.0f };
	const VECTOR firstRota = { -0.9f,0,-0.02f };
};

