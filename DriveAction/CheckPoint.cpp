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
bool CheckPoint::CheckPointUpdate(ConflictExamineResultInfo carInfo)
{  
    HitChecker checker;
    ConflictExamineResultInfo thisInfo = {};//このチェックポイントクラスの情報
    thisInfo.radius = radius;
    //何回かだけチェックポイントを通過したか調べる
    for (int i = 0; i < vectorExamineCount; i++)
    {
        int count = (transitCheckPointCount + i) % vecSize;
        count = count > vecSize ? vecSize : count;
        thisInfo.pos = GetArgumentCountVector(cPParam.positionVec.begin(), count);
        if (checker.HitCheck(carInfo, thisInfo))
        {
            VECTOR startPos = VAdd(VScale(VCross(direction, VGet(0, 1, 0)), radius), position);
            VECTOR endPos = VAdd(VScale(VCross(direction, VGet(0, -1, 0)), radius), position);
            VECTOR dir = VSub(endPos, startPos);
            VECTOR dir2 = VSub(carInfo.pos, startPos);
            float crossY = VCross(VNorm(dir), VNorm(dir2)).y;
            if (crossY > 0)
            {
                transitCheckPointCount += i + 1;
                //1週したなら
                if (transitCheckPointCount >= vecSize)
                {
                    goalCount++;
                    transitCheckPointCount = 0;
                }
                position = GetArgumentCountVector(cPParam.positionVec.begin(), transitCheckPointCount % vecSize);
                direction = GetArgumentCountVector(cPParam.directionVec.begin(), transitCheckPointCount % vecSize);

                return true;
            }
        }
    }
    //最後に目標地点までどのぐらい離れてるか
    checkPointDistance = VSize(VSub(position,carInfo.pos));
    return false;
}

/// <summary>
/// 他のCPUにもコピーさせるために渡す
/// </summary>
/// <returns></returns>
CircuitData CheckPoint::GetCheckPoint() const 
{
    return cPParam;
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




