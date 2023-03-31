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
    cPParam.positionVec = GetVectorConversion(CourceDataLoader::GetVECTORData(checkPointPosPass));
    cPParam.directionVec = GetVectorConversion(CourceDataLoader::GetVECTORData(checkPointDirPass));
    vecSize = cPParam.positionVec.size();
    
}
CheckPoint::~CheckPoint()
{
}

/// <summary>
/// プレイヤーがぶつかったら次の行き先を設定する
/// </summary>
/// <param name="carInfo">ぶつかったか調べる車</param>
bool CheckPoint::IsTransitCheckPoint(int transitCount, HitCheckExamineObjectInfo carInfo)
{  
    VECTOR carPos = carInfo.pos;
    carPos.y = 0;
    VECTOR pos = cPParam.positionVec[transitCount% vecSize];
    VECTOR dir = cPParam.directionVec[transitCount% vecSize];
    //通過したか判定する
    if (IsTransitCheckPointCar(pos, dir, carPos))
    {
        //通過したら処理終了
        return true;
    }
    return false;
}

bool CheckPoint::IsTransitCheckPointCar(VECTOR pos, VECTOR dir, VECTOR carPos)
{
    VECTOR rightEdge = VAdd(VCross(dir, VGet(0, 1, 0)), pos);
    VECTOR leftEdge = VAdd(VCross(dir, VGet(0, -1, 0)), pos);
    //右端と左端を繋げ単位化
    VECTOR normLineSegment = VNorm(VSub(rightEdge,leftEdge));
    //左端から車までの距離
    VECTOR leftEdgeAndCarBetween = VSub(carPos, leftEdge);
    //チェックポイントまでの距離
    VECTOR tempVec = VScale(normLineSegment, VDot(normLineSegment, leftEdgeAndCarBetween));
    //通過したら外積のYが0より大きくなる。ある程度近寄っている必要もある
    if (VCross(normLineSegment, leftEdgeAndCarBetween).y > 0)
    {
        return true;
    }
    return false;
}

/// <summary>
/// チェックポイントまでの距離
/// </summary>
/// <returns></returns>
float CheckPoint::GetCheckPointDistance(int transitCount, VECTOR objPos)
{
    VECTOR dir = cPParam.directionVec[transitCount];
    VECTOR pos = cPParam.positionVec[transitCount];
    VECTOR rightEdge = VAdd(VCross(dir, VGet(0, 1, 0)), pos);
    VECTOR leftEdge = VAdd(VCross(dir, VGet(0, -1, 0)), pos);
    //右端と左端を繋げ単位化
    VECTOR normLineSegment = VNorm(VSub(rightEdge, leftEdge));
    //左端から車までの距離
    VECTOR leftEdgeAndCarBetween = VSub(objPos, leftEdge);
    //チェックポイントまでの距離
    VECTOR tempVec = VScale(normLineSegment, VDot(normLineSegment, leftEdgeAndCarBetween));
    return VSize(tempVec);
}

int CheckPoint::GetGoalCount(int transitCount)
{
    return transitCount / vecSize;
}

VECTOR CheckPoint::GetCheckPointPos(int transitCount)
{
    return cPParam.positionVec[transitCount%vecSize];
}

VECTOR CheckPoint::GetCheckPointDir(int transitCount)
{
    return cPParam.directionVec[transitCount%vecSize];
}
