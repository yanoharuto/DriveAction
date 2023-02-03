#include "CheckPoint.h"
#include "VECTOR3Loader.h"
#include "HitChecker.h"
#include "Utility.h"
#include "ListUtility.h"
#include "OriginalMath.h"
/// <summary>
/// デフォルトコンストラクタ
/// </summary>
/// <returns></returns>
CheckPoint::CheckPoint()
{
    direction = {};
    vecSize = 0;
}

/// <summary>
/// コース情報複製用
/// </summary>
/// <param name="checkPointParam"></param>
/// <returns></returns>
CheckPoint::CheckPoint(const CircuitData circuitData)
{
    cPParam = circuitData;
    vecSize = circuitData.positionVec.size();
    checkPointDistance = 0;
    InitMember();
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
    HitCheckExamineObjectInfo thisInfo = {};//このチェックポイントクラスの情報
    ConflictExamineResultInfo conflictInfo;
    conflictInfo.SetObjInfo(false, this);
    thisInfo.radius = radius;
    //何回かだけチェックポイントを通過したか調べる
    for (int i = 0; i < checkPointExamineCount; i++)
    {
        int count = (transitCheckPointCount + i) % vecSize;
        count = count > vecSize ? vecSize : count;
        VECTOR pos = GetArgumentCountVector(cPParam.positionVec.begin(), count);
        VECTOR dir = GetArgumentCountVector(cPParam.directionVec.begin(), count);
        //通過したときは外積のYがプラスになる
        if (IsTransitCheckPointCar(pos,dir,carInfo.pos))
        {
            //チェックポイント通過回数加算
            transitCheckPointCount += i + 1;
            position = GetArgumentCountVector(cPParam.positionVec.begin(), transitCheckPointCount % vecSize);
            direction = GetArgumentCountVector(cPParam.directionVec.begin(), transitCheckPointCount % vecSize);
            conflictInfo.pos = position;
            conflictInfo.dir = direction;
            conflictInfo.hitFlag = true;
            //1週したなら
            if (transitCheckPointCount >= vecSize)
            {
                goalCount++;
                transitCheckPointCount = 0;
            }
            return conflictInfo;
        }
        else if (VSize(VSub(position,carInfo.pos))< radius)
        {
            conflictInfo.dir= GetArgumentCountVector(cPParam.directionVec.begin(), transitCheckPointCount % vecSize);
            conflictInfo.hitFlag = true;
            return conflictInfo;
        }
    }

    return conflictInfo;
}

bool CheckPoint::IsTransitCheckPointCar(VECTOR pos, VECTOR dir, VECTOR carPos)
{
    //startPosからendPosまでの間を通過処理
    VECTOR rightEdge = VAdd(VScale(VCross(dir, VGet(0, 1, 0)), radius), pos);
    VECTOR leftEdge = VAdd(VScale(VCross(dir, VGet(0, -1, 0)), radius), pos);
    //線分
    VECTOR normLineSegment = VNorm(VSub(rightEdge,leftEdge));
    VECTOR leftEdgeAndCarBetween = VSub(carPos, leftEdge);
    VECTOR tempVec = VScale(normLineSegment, VDot(normLineSegment, leftEdgeAndCarBetween));
    checkPointDistance = VSize(VSub(tempVec, leftEdgeAndCarBetween));
    if (VCross(normLineSegment, leftEdgeAndCarBetween).y > 0 && checkPointDistance < radius / 2)
    {
        return true;
    }
    return false;
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
    return transitCheckPointCount + goalCount * vecSize;
}
/// <summary>
/// チェックポイントまでの距離
/// </summary>
/// <returns></returns>
float CheckPoint::GetCheckPointDistance()
{
    return checkPointDistance;
}
;
/// <summary>
/// 初期化処理
/// </summary>
void CheckPoint::InitMember()
{
    tag = ObjectTag::goal;
    position = cPParam.positionVec.front();
    direction = cPParam.directionVec.front();
    radius = goalRadius;
    vecSize = cPParam.positionVec.size();
}




