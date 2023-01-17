#include "Car.h"
#include "Wheels.h"
#include "Utility.h"
#include "ArgumentObjInfoStruct.h"
#include <math.h>
Car::Car()
{
	tag = ObjectTag::car;
	radius = radiusValue;
	UpdateMV1Pos();
	ModelSetMatrix();
	destinationPos = {};
	wheels = new Wheels(ArgumentCarInfo{ MV1GetMatrix(modelHandle),direction,VSize(velocity) });
}

Car::Car(VECTOR firstPos, VECTOR firstDir)
{
	position = firstPos;
	direction = firstDir;
	tag = ObjectTag::car;
	radius = radiusValue;
	UpdateMV1Pos();
	ModelSetMatrix();
	destinationPos = {};
	wheels = new Wheels(ArgumentCarInfo{ MV1GetMatrix(modelHandle),direction,VSize(velocity) });
}

Car::~Car()
{
	MV1DeleteModel(modelHandle);
	SAFE_DELETE(wheels);
}

void Car::ConflictProcess(float deltaTime,const ArgumentConflictInfo conflictInfo)
{
	switch (conflictInfo.tag)
	{
	case ObjectTag::car:
	case ObjectTag::stage:
	case ObjectTag::obstacle:
		ConflictReaction(deltaTime,conflictInfo.pos, radius);
		break;
	case ObjectTag::goal:
		destinationPos = conflictInfo.pos;
		break;
	default:
		break;
	}
}

void Car::Draw()
{
	MV1DrawModel(modelHandle);
	wheels->Draw();
}

/// <summary>
/// ぶつかった時の処理　減速する
/// </summary>
/// <param name="conflictObjPos"></param>
/// <param name="conflictObjRad"></param>
void Car::ConflictReaction(float deltaTime, const VECTOR conflictObjPos, const float conflictObjRad)
{
	accelPower -= accelPower * colideDecel;
	VECTOR nVSub = VSub(position,conflictObjPos);
	nVSub = VNorm(nVSub);
	nVSub = VScale(nVSub,conflictObjRad);
	nVSub.y = 0;
	position = VAdd(position, nVSub);
}

void Car::DamageReaction(const VECTOR conflictObjPos, const float conflictObjRad)
{
}

/// <summary>
/// 進む方向と速さを更新する
/// </summary>
/// <param name="deltaTime">経過時間</param>
/// <param name="accelVec">次の更新までに進む方向と速さ</param>
void Car::UpdateVelocity(const VECTOR accelVec)
{
	velocity = accelVec;
	//タイヤの向きから進行方向を取る
	float theta = wheels->GetMoveDirTheta(VSize(velocity));
	theta *= gripPower;
	velocity = VTransform(velocity, MGetRotY(theta));
	// ベロシティ加速計算.


	// 上下方向にいかないようにベロシティを整える.
	velocity = VGet(velocity.x, 0, velocity.z);	
}
/// <summary>
/// modelの描画場所を更新
/// </summary>
void Car::UpdateMV1Pos()
{
	// 力をかけ終わったベロシティの方向にディレクションを調整.
	if (VSize(velocity) != 0)
	{
		direction = VNorm(velocity);
	}
	// ポジションを更新.
	position = VAdd(position, velocity);
	// ３Dモデルのポジション設定
	MV1SetPosition(modelHandle, position);
}
/// <summary>
/// 車を回転させる
/// </summary>
void Car::ModelSetMatrix()
{
	// 向きに合わせて回転.
	MV1SetRotationZYAxis(modelHandle, direction, VGet(0.0f, 1.0f, 0.0f), 0.0f);
	// モデルに向いてほしい方向に回転.
	MATRIX tmpMat = MV1GetMatrix(modelHandle);
	MATRIX rotYMat = MGetRotY(180.0f * rage);
	tmpMat = MMult(tmpMat, rotYMat);
	MV1SetRotationMatrix(modelHandle, tmpMat);
}
/// <summary>
/// 自動操縦。
/// </summary>
/// <param name="deltaTime">フレーム間差分</param>
/// <param name="outsideHitFlag">コース外に出たか</param>
void Car::AutoDrive(const float deltaTime, const bool outsideHitFlag)
{
	ArgumentCarInfo info;
	info.handleDir = GetHandleDir();
	VECTOR accelVec = GetAccelVec(info.handleDir, outsideHitFlag, deltaTime);
	UpdateVelocity(VScale(accelVec, deltaTime));
	UpdateMV1Pos();
	ModelSetMatrix();
	info.matrix = MV1GetMatrix(modelHandle);
	info.velocitySize = VSize(velocity);
	info.direction = direction;

	wheels->WheelUpdate(info);
}

HandleDirection Car::GetHandleDir()
{
	float destinationDir = 0;//目的地との距離のずれ
	VECTOR distance = VSub(destinationPos, position);
	destinationDir = VDot(direction, distance) / (VSize(distance) * VSize(direction));
	destinationDir = acosf(destinationDir) / rage;

	if (destinationDir > turnProccesLine)
	{
		//車の向いてる方向と目的地までの方向の外積を出して
		//右に曲がるか左に曲がるか調べる
		float crossY = VCross(VNorm(direction), VNorm(distance)).y;
		if (crossY > 0)
		{
			return HandleDirection::right;
		}
		else
		{
			return HandleDirection::left;
		}
	}
	
	return HandleDirection::straight;
}

/// <summary>
/// 加速するための処理
/// </summary>
/// <param name="dir">向かってる方向</param>
/// <param name="outsideHitFlag"></param>
/// <returns></returns>
VECTOR Car::GetAccelVec(HandleDirection handleDir, bool outsideHitFlag, float deltaTime)
{
	// 加速処理.
	VECTOR accelVec = VGet(0, 0, 0);
	accelPower += accelPower > maxSpeed ? 0 : accelSpeed * deltaTime;

	// 止まっている場合は減速しない.
	if (VSize(velocity) > 0)
	{
		//左右に曲がろうとしていたら減速
		if (handleDir != HandleDirection::straight)
		{
			//左右に曲がろうとしたら減速する
			accelPower -= accelPower * gripDecel * deltaTime;
		}
		//コース外に出たら減速
		if (outsideHitFlag)
		{
			accelPower -= accelPower * outsideHitDecel * deltaTime;
		}
	}
	accelVec = VScale(direction, accelPower);
	return accelVec;
}