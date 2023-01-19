#pragma once
#include "DxLib.h"
//ハンドルがどっち向きなのか
enum class HandleDirection
{	
	straight,
	left,
	right,
};
/// <summary>
/// タイヤ一つ一つが持っている情報
/// </summary>
struct Wheel
{
	int modelHandle = -1;//Duplicateするので本体は別
	VECTOR betweenBody = {};//車までの距離
	MATRIX matrix;
};
/// <summary>
/// タイヤに引数で渡してほしい車の情報
/// </summary>
struct WheelArgumentCarInfo
{
	MATRIX matrix;//車のmodelの行列
	VECTOR direction;//車の向き
	float velocitySize;//速さの大きさ
	HandleDirection handleDir;	//ハンドルがどっち向きなのか
};

/// <summary>
/// 車が走る向きを渡すよ。あとタイヤが回転したり描画する
/// </summary>
class Wheels 
{
public:
    Wheels(const WheelArgumentCarInfo InitInfo);
    ~Wheels();
    /// <summary>
    /// 描画
    /// </summary>
    void Draw();

	/// <summary>
	/// 左右キーを入力したら傾け、上下キーで回転させる
	/// </summary>
	/// <param name="_Key">入力情報</param>
	void WheelUpdate(const WheelArgumentCarInfo info);

	/// <summary>
	/// どの向きに曲がればいいかタンジェントを返すよ
	/// </summary>
	/// <param name="velocitySize">速さのベクトルの大きさ</param>
	/// <returns>負の数ならだったら左</returns>
	float GetMoveDirTheta(const float velocitySize);
private:	
	/// <summary>
	/// 煙のエフェクトが出る
	/// </summary>
	/// <param name="pos"></param>
	void StartSmokeEffect(VECTOR pos);
	/// <summary>
	/// 全てのタイヤのマトリックスをセットする
	/// </summary>
	void AllSetWheelMatrix();
	/// <summary>
/// 回転するための半径を返す
/// </summary>
/// <param name="firstWheelRota"></param>
/// <returns></returns>
	float GetRotationRadius(const float firstWheelRota);
	/// <summary>
    /// 車から見たタイヤの座標が返ってくる
    /// </summary>
    /// <param name="_wheel"></param>
	VECTOR WheelGetPos(const Wheel& wheel);
	/// <summary>
    /// タイヤの位置と回転を設定
    /// </summary>
    /// <param name="_wheel">設定したいタイヤ</param>
    /// <param name="_rotaX">タイヤの転がるときの回転</param>
    /// <param name="_rotaY">タイヤの向きがずれるときの回転</param>
	void SetWheelMatrix(Wheel& wheel, const float rotaX, const float rotaY);
	/// <summary>
	/// タイヤの初期化
	/// </summary>
	/// <param name="_Wheel">初期化したいタイヤ</param>
	/// <param name="_ModelHandle">タイヤのモデル</param>
	/// <param name="_Pos">車から見た位置</param>
	/// <param name="_Rota">回転角</param>
	void InitWheel(Wheel& wheel, int DuplicateSourceModel, VECTOR pos, float rota);

	
	const float firstLWheelRota = 0.0f;		//左側タイヤの初期角度
	const float firstRWheelRota = 180.0f;		//右側タイヤの初期角度
	const float wheelDriveRotaPower = 200.0f;//車の回転力
	const float wheelCurvePower = 1.7f;//タイヤが左右に傾く力
	const float maxWheelRotaY = 45.5f;//この角度までタイヤは傾くよ
	const float rotaCalculationLine = 1.2f;//進行方向に影響するまでに必要なタイヤの角度
	const float rage = static_cast<float>(DX_PI / 180.0f);
	float wheelDriveSpeed = 0.0f;//車の回転速度
	float wheelDriveRota = 0.0f;//車の左右への傾き
	int effectResourceHandle = -1;//煙のエフェクト
	bool isStraightDash;//まっすぐ進んでいるかどうか
	int modelHandle;//タイヤのモデルハンドル
	Wheel lFWheel;
	Wheel lBWheel;
	Wheel rFWheel;
	Wheel rBWheel;
	WheelArgumentCarInfo carInfo;
	VECTOR wheelEffectPos;
	const VECTOR fWheelPos = { 2.7f,-0.8f,1.6f };
	const VECTOR bWheelPos = { 2.4f,-0.8f,1.6f };
};