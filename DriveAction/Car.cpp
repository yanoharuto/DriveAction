#include "Car.h"
#include "Wheels.h"
#include "Utility.h"
Car::Car()
{
	tag = ObjectTag::car;
	radius = radiusValue;
	// ３Dモデルのポジション設定
	MV1SetPosition(modelHandle, position);
	// 向きに合わせて回転.
	MV1SetRotationZYAxis(modelHandle, direction, VGet(0.0f, 1.0f, 0.0f), 0.0f);
	// モデルに向いてほしい方向に回転.
	MATRIX tmpMat = MV1GetMatrix(modelHandle);
	MATRIX rotYMat = MGetRotY(180.0f * rage);
	tmpMat = MMult(tmpMat, rotYMat);
	MV1SetRotationMatrix(modelHandle, tmpMat);
	destinationPos = {};
	wheels = new Wheels(ArgumentCarInfo{ MV1GetMatrix(modelHandle),direction,VSize(velocity) });
}

Car::~Car()
{
	MV1DeleteModel(modelHandle);
	SAFE_DELETE(wheels);
}

void Car::ConflictProcess(const ArgumentConflictInfo conflictInfo)
{
	switch (conflictInfo.tag)
	{
	case ObjectTag::car:
	case ObjectTag::stage:
	case ObjectTag::obstacle:
		ConflictReaction(conflictInfo.pos, conflictInfo.radius);
		break;
	case ObjectTag::goal:
		destinationPos = conflictInfo.pos;
#ifdef _DEBUG
		printfDx("%f,%f\n", conflictInfo.pos.x, conflictInfo.pos.z);
		printfDx("%f,%f\n", destinationPos.x, destinationPos.z);
#endif
		break;
	default:
		break;
	}
}

void Car::Draw()
{
	MV1DrawModel(modelHandle);
	wheels->Draw();
#ifdef _DEBUG
	DrawSphere3D(position,radius,5,GetColor(100,100,255), GetColor(100, 100, 255),false);
#endif
}

void Car::ConflictReaction(const VECTOR conflictObjPos, const float conflictObjRad)
{
	VECTOR nVSub = VSub(position,conflictObjPos);
	nVSub = VNorm(nVSub);
	accelPower -= accelPower * colideDecel;
	nVSub = VScale(nVSub,colideDecel);
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
void Car::UpdateVelocity(const float deltaTime, const VECTOR accelVec)
{
	//タイヤの向きから進行方向を取る
	float theta = wheels->GetMoveDirTheta(VSize(velocity));
	theta *= gripPower;
	velocity = VTransform(velocity, MGetRotY(theta));
	// ベロシティ加速計算.
	velocity = VScale(VAdd(velocity, accelVec), deltaTime);
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
