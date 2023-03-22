#include "CheckPoint.h"
#include "VECTOR3Loader.h"
#include "HitChecker.h"
#include "Utility.h"
#include "ListUtility.h"
#include "OriginalMath.h"
#include "CourceDataLoader.h"
#include "CircuitDataStruct.h"
//車はDirと反対向きなので内積を取って1に近かったらゴールした判定
static const float dirJugeLine = 0.8f;
//次のチェックポイントまでの向きを出し始める範囲
static const float goalRadius = 150.0f;
//サーキットのデータ
static CircuitData cPParam;
/// <summary>
/// デフォルトコンストラクタ
/// </summary>
/// <returns></returns>
CheckPoint::CheckPoint()
{
    direction = {};
    vecSize = 0;
    tag = ObjectTag::goal;
    cPParam.positionVec = CourceDataLoader::GetCheckPointPosList();
    cPParam.directionVec = CourceDataLoader::GetCheckPointDirList();
    vecSize = cPParam.positionVec.size();
    checkPointDistance = 0;
    position = cPParam.positionVec.front();
    direction = cPParam.directionVec.front();
    radius = goalRadius;
    vecSize = cPParam.positionVec.size();
    transitCount = 0;
}
CheckPoint::~CheckPoint()
{
}

/// <summary>
/// プレイヤーがぶつかったら次の行き先を設定する
/// </summary>
/// <param name="carInfo">ぶつかったか調べる車</param>
ConflictExamineResultInfo CheckPoint::CheckPointUpdate(HitCheckExamineObjectInfo carInfo)
{  
    HitChecker checker;
    //チェックポイントの位置と向き情報
    ConflictExamineResultInfo conflictInfo;
    conflictInfo.SetObjInfo(false, this);

    VECTOR carPos = carInfo.pos;
    carPos.y = 0;
    VECTOR pos = GetArgumentCountVector(cPParam.positionVec.begin(), transitCount % vecSize);
    VECTOR dir = GetArgumentCountVector(cPParam.directionVec.begin(), transitCount % vecSize);
    //通過したか判定する
    if (IsTransitCheckPointCar(pos, dir, carPos))
    {
        //チェックポイント通過回数加算
        transitCount++;
        //通過したら次のチェックポイントの場所を更新
        position = GetArgumentCountVector(cPParam.positionVec.begin(), transitCount % vecSize);
        direction = GetArgumentCountVector(cPParam.directionVec.begin(), transitCount % vecSize);
        //一周したらGoalCountをインクリメント
        if (transitCount >= vecSize)
        {
            goalCount++;
            transitCount = 0;
        }
        conflictInfo.pos = position;
        conflictInfo.dir = direction;
        conflictInfo.hitFlag = true;
        //通過したら処理終了
        return conflictInfo;
    }/*
    else if (checkPointDistance < radius)
    {
        conflictInfo.pos = GetArgumentCountVector(cPParam.positionVec.begin(), (transitCount + 1) % vecSize);
        conflictInfo.dir = GetArgumentCountVector(cPParam.directionVec.begin(), (transitCount + 1) % vecSize);
        return conflictInfo;
    }*/
    return conflictInfo;
}

bool CheckPoint::IsTransitCheckPointCar(VECTOR pos, VECTOR dir, VECTOR carPos)
{
    
    VECTOR rightEdge = VAdd(VCross(dir, VGet(0, 1, 0)), pos);
    VECTOR leftEdge = VAdd(VCross(dir, VGet(0, -1, 0)), pos);
    //右端と左端を繋げ単位化
    VECTOR normLineSegment = VNorm(VSub(rightEdge,leftEdge));
    //左端から車までの距離
    VECTOR leftEdgeAndCarBetween = VSub(carPos, leftEdge);
    //チェックポイントまでの距離を更新
    VECTOR tempVec = VScale(normLineSegment, VDot(normLineSegment, leftEdgeAndCarBetween));
    checkPointDistance = VSize(VSub(tempVec, leftEdgeAndCarBetween));
    //通過したら外積のYが0より大きくなる。ある程度近寄っている必要もある
    if (VCross(normLineSegment, leftEdgeAndCarBetween).y > 0 && checkPointDistance < radius)
    {
        return true;
    }
    return false;
}

VECTOR CheckPoint::GetLastPos()
{
    return GetArgumentCountVector(cPParam.positionVec.begin(), transitCount - 1);
}

VECTOR CheckPoint::GetLastDir()
{
    return GetArgumentCountVector(cPParam.directionVec.begin(), transitCount - 1);
}

/// <summary>
/// ゴールした回数を返す
/// </summary>
/// <returns></returns>
int CheckPoint::GetGoalCount()
{
    return goalCount;
}
int CheckPoint::GetTransitCheckPointCount()
{
    return transitCount + goalCount * vecSize;
}
/// <summary>
/// チェックポイントまでの距離
/// </summary>
/// <returns></returns>
float CheckPoint::GetCheckPointDistance()
{
    return checkPointDistance;
}

bool CheckPoint::HitCheckConflict(HitCheckExamineObjectInfo objInfo)
{
    objInfo.pos.y = 0;
    HitChecker checker;
    return checker.HitCheck(this,objInfo);
}