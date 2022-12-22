#include "Player.h"
#include <math.h>
// 静的定数.
const float Player::ACCEL = 3.0f;			 // 通常の加速.
const float Player::MAX_SPEED = 180.0f;		 // 最高速度.	
const float Player::DEFAULT_DECEL = -0.004f;	 // なにもしない時の減速.	
const float Player::BREAK_DECEL = -0.075f;	 // ブレーキ時の減速.	
const float Player::GRIP_DECEL = -0.025f;	 // グリップの減速.	
const float Player::GRIP_POWER = 1.2f;		 // グリップ力.	
const float Player::MAX_GRIP_POWER = 0.4f;		 // グリップ力.	
const float Player::COLIDE_DECEL_FAC = 0.4f; // 障害物にぶつかったときの減速率.	
/// <summary>
/// コンストラクタ
/// </summary>
/// <returns></returns>
Player::Player()
{
    modelHandle = MV1LoadModel("data/model/Player/RedCar.mv1");
	wheeleModelHandle = MV1LoadModel("data/model/Player/Wheel.mv1");
	position = firstPos;
	direction = firstRota;
	// ３Dモデルのポジション設定
	MV1SetPosition(modelHandle, position);
	// 向きに合わせて回転.
	MV1SetRotationZYAxis(modelHandle, direction, VGet(0.0f, 1.0f, 0.0f), 0.0f);
	// モデルに向いてほしい方向に回転.
	MATRIX tmpMat = MV1GetMatrix(modelHandle);
	MATRIX rotYMat = MGetRotY(180.0f * (float)(DX_PI / 180.0f));
	tmpMat = MMult(tmpMat, rotYMat);
	MV1SetRotationMatrix(modelHandle, tmpMat);
	InitWheele(lFWheel, wheeleModelHandle, VGet(-fWheelPos.x,fWheelPos.y,-fWheelPos.z),firstLWheeleRota);
	InitWheele(lBWheel, wheeleModelHandle, VGet(bWheelPos.x, fWheelPos.y,-fWheelPos.z),firstLWheeleRota);
	InitWheele(rBWheel, wheeleModelHandle, VGet(bWheelPos.x, fWheelPos.y,fWheelPos.z),firstRWheeleRota);
	InitWheele(rFWheel, wheeleModelHandle, VGet(-fWheelPos.x, fWheelPos.y,fWheelPos.z),firstRWheeleRota);
}

/// <summary>
/// デストラクタ
/// </summary>
/// <returns></returns>
Player::~Player()
{
	MV1DeleteModel(modelHandle);
	MV1DeleteModel(wheeleModelHandle);
	MV1DeleteModel(lFWheel.modelHandle);
	MV1DeleteModel(rFWheel.modelHandle);
	MV1DeleteModel(lBWheel.modelHandle);
	MV1DeleteModel(rBWheel.modelHandle);
}

/// <summary>
/// 更新
/// </summary>
void Player::Update(const float deltaTime)
{
	float theta = 0;
	// 右を押していたら右方向に力をかける
	if (wheelDriveRota > rotaCalculationLine)
	{
		theta = GetCircleRadius(firstRWheeleRota);
		theta = atan2f(VSize(velocity), theta);
	}
	// 左を押していたら左方向に力をかける
	else if (wheelDriveRota < -rotaCalculationLine)
	{
		theta = GetCircleRadius(firstLWheeleRota);
		theta = atan2f(VSize(velocity), theta);
		theta = -theta;
	}
	theta *= GRIP_POWER;
	velocity = VTransform(velocity,MGetRotY(theta));

	// キー入力取得
	int Key = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	// 加速処理.
	VECTOR accelVec = VGet(0, 0, 0);
	// 上を押していたら加速.
	if (Key & PAD_INPUT_UP)
	{
		accel += accel > MAX_SPEED ? 0 : ACCEL;

		accelVec = VScale(direction, accel);
	}
	// 下を押していたら減速.
	else if (Key & PAD_INPUT_DOWN)
	{
		accel += accel * BREAK_DECEL;
		accelVec = VScale(direction, accel);
	}
	// 止まっている場合は減速しない.
	if (VSize(velocity) > 0)
	{
		// 右か左を押していたらグリップによる減速.
		if (Key & PAD_INPUT_RIGHT || Key & PAD_INPUT_LEFT)
		{
			accel += accel * GRIP_DECEL;
			accelVec = VScale(direction, accel);
		}
		// 何も押さなければ減速.
		if (Key == 0)
		{
			accel += accel * DEFAULT_DECEL;
			accelVec = VScale(direction, accel);
		}
	}

	// ベロシティ加速計算.
	velocity = VScale(VAdd(velocity, accelVec),deltaTime);

	// 上下方向にいかないようにベロシティを整える.
	velocity = VGet(velocity.x, 0, velocity.z);
	// 反対方向に進む状態になっていたら止める.
	if (VDot(velocity, direction) < 0)
	{
		velocity = VGet(0, 0, 0);
	}
	// 力をかけ終わったベロシティの方向にディレクションを調整.
	if (VSize(velocity) != 0)
	{
		direction = VNorm(velocity);
	}
	// ポジションを更新.
	position = VAdd(position, velocity);
	// ３Dモデルのポジション設定
	MV1SetPosition(modelHandle, position);

	// 向きに合わせて回転.
	MV1SetRotationZYAxis(modelHandle, direction, VGet(0.0f, 1.0f, 0.0f), 0.0f);
	// モデルに向いてほしい方向に回転.
	MATRIX tmpMat = MV1GetMatrix(modelHandle);
	MATRIX rotYMat = MGetRotY(180.0f * (float)(DX_PI / 180.0f));
	tmpMat = MMult(tmpMat, rotYMat);
	MV1SetRotationMatrix(modelHandle, tmpMat);

	WheelUpdate(Key);

#ifdef _DEBUG
	//printfDx("%f,%f,%f:\n", tmpMat.m[0][0], tmpMat.m[0][1], tmpMat.m[0][2]) ;
	//printfDx("%f,%f,%f:\n", tmpMat.m[1][0], tmpMat.m[1][1], tmpMat.m[1][2]) ;
	//printfDx("%f,%f,%f:\n", tmpMat.m[2][0], tmpMat.m[2][1], tmpMat.m[2][2]) ;

	printfDx("%f,%f,%f:\n", position.x, position.y, position.z);
	printfDx("%f,%f,%f:\n", direction.x, direction.y, direction.z);
	
#endif // _DEBUG
}
/// <summary>
/// 描画
/// </summary>
void Player::Draw()
{
	MV1DrawModel(modelHandle);
	MV1DrawModel(lBWheel.modelHandle);
	MV1DrawModel(lFWheel.modelHandle);
	MV1DrawModel(rFWheel.modelHandle);
	MV1DrawModel(rBWheel.modelHandle);
}
/// <summary>
/// タイヤの初期化
/// </summary>
/// <param name="_Wheele">初期化したいタイヤ</param>
/// <param name="_ModelHandle">コピーしたいモデル</param>
/// <param name="_Pos">タイヤの位置</param>
/// <param name="_Rota">タイヤの初期角度</param>
void Player::InitWheele(Wheel& wheel, int modelHandle, VECTOR pos, float rota)
{
	wheel.modelHandle = MV1DuplicateModel(modelHandle);
	wheel.betweenBody = pos;
	VECTOR wheelPos = WheelGetPos(wheel);
	MATRIX bodyMat = MV1GetMatrix(modelHandle);
	wheel.matrix = MMult(MGetRotY(rota*DX_PI/180.0f), MMult(bodyMat,MGetTranslate(wheelPos)));
	MV1SetMatrix(wheel.modelHandle, wheel.matrix);
}
/// <summary>
/// 左右キーを入力したら傾け、上下キーで回転させる
/// </summary>
/// <param name="_Key">入力情報</param>
void Player::WheelUpdate(const int key)
{
	MATRIX bodyMat = MV1GetMatrix(modelHandle);
	MATRIX wheelRota;//タイヤの回転
	MATRIX wheelPos;//タイヤのポジション
	//左前タイヤ
	SetWheelMatrix(lFWheel, wheelDriveSpeed, firstLWheeleRota + wheelDriveRota);
	//左後ろタイヤ
	SetWheelMatrix(lBWheel, wheelDriveSpeed, firstLWheeleRota);
	//右前タイヤ	
	SetWheelMatrix(rFWheel, -wheelDriveSpeed, firstRWheeleRota + wheelDriveRota);
	//右後ろタイヤ
	SetWheelMatrix(rBWheel, -wheelDriveSpeed, firstRWheeleRota);
	if (VSize(velocity) > 0)
	{
		wheelDriveSpeed = -VSize(velocity) * wheeleDriveRotaSpeed;
	}
	else
	{
		wheelDriveSpeed = 0;
	}
	//タイヤを傾ける処理
	if (key & PAD_INPUT_RIGHT)
	{
		if (wheelDriveRota < maxWheelRota)
		{
			wheelDriveRota += wheelCurvePower;
		}
		else
		{
			wheelDriveRota = maxWheelRota;
		}
	}
	else if (key & PAD_INPUT_LEFT)
	{
		if (wheelDriveRota > -maxWheelRota)
		{
			wheelDriveRota -= wheelCurvePower;
		}
		else
		{
			wheelDriveRota = -maxWheelRota;
		}
	}
	//どっちも押されてなかったらタイヤを元に戻す
	else if (fabsf(wheelDriveRota) != rotaCalculationLine)
	{
		wheelDriveRota += wheelDriveRota > 0 ? -wheelCurvePower : wheelCurvePower;
	}
}
/// <summary>
/// タイヤの位置が帰ってくる
/// </summary>
/// <param name="_wheel">位置が分からないタイヤ</param>
/// <returns>タイヤの位置</returns>
VECTOR Player::WheelGetPos(const Wheel& wheel)
{
	//タイヤの前方方向の位置
	VECTOR between = VScale(direction, -wheel.betweenBody.x);
	//タイヤの横方向の位置と足す
	between =VAdd(between,VScale(VCross(direction, VGet(0, 1, 0)), -wheel.betweenBody.z));
	//高さを合わせる
	between.y = fWheelPos.y;
	return  between;
}
/// <summary>
/// タイヤの位置と回転を設定
/// </summary>
/// <param name="_wheel">設定したいタイヤ</param>
/// <param name="_rotaX">タイヤの転がるときの回転</param>
/// <param name="_rotaY">タイヤの向きがずれるときの回転</param>
void Player::SetWheelMatrix(Wheel& wheel,float rotaX,float rotaY)
{
	//タイヤの位置を車の向きに合わせる
	MATRIX wheelPos = MMult(MV1GetMatrix(modelHandle), MGetTranslate(WheelGetPos(wheel)));
	
	MATRIX wheelRota = MMult(MGetRotX(rotaX * DX_PI / 180.0f), MGetRotY(rotaY * DX_PI / 180.0f));
	wheel.matrix = MMult(wheelRota,wheelPos);
	MV1SetMatrix(wheel.modelHandle,wheel.matrix);
}

float Player::GetCircleRadius(float firstWheelRota)
{
	if (fabsf(wheelDriveRota) > rotaCalculationLine)
	{
		float rota = tan(fabsf(wheelDriveRota) * DX_PI / 180);
		//回転半径を出す
		float radius = (fWheelPos.x + bWheelPos.x) / rota;
		//車の向きに後ろタイヤをY軸分回転させる
		VECTOR bWDir = VTransform(direction, MGetRotY((firstWheelRota) * DX_PI / 180));
		//後ろタイヤの横向きを出す
		bWDir = VNorm(VCross(bWDir, VGet(0, 1, 0)));
		//回転半径の中心座標を出す
		VECTOR circleAxisPos = VScale(bWDir, radius);

		//進行方向に必要な回転を出す
		return  VSize(circleAxisPos);
	}
	return 0.0f;
}