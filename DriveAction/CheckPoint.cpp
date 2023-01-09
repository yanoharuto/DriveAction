#include "CheckPoint.h"
#include "VECTOR3Loader.h"
#include "HitChecker.h"
#include "Utility.h"
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
    InitMember();
}

CheckPoint::~CheckPoint()
{
}

/// <summary>
/// プレイヤーがぶつかったら次の行き先を設定する
/// </summary>
/// <param name="carInfo">ぶつかったか調べる車</param>
bool CheckPoint::CheckPointUpdate(ArgumentConflictInfo carInfo)
{  
    HitChecker checker;
    for (int i = 0; i < vectorExamineCount; i++)
    {
        //車がベクターの地点を通過してないか調べる
        if (checker.HitCheck(this, carInfo))
        {
            float theta = VDot(carInfo.dir, direction);
            //ぶつかった相手が逆走してなかったら次のチェックポイントに行く
            if (theta > dirJugeLine)
            {
                transitCheckPointCount += i + 1;
                //ゴールより先に行ったら最初のチェックポイントを取る
                if (transitCheckPointCount >= static_cast<int>(cPParam.positionVec.size()))
                {
                    transitCheckPointCount = 0;
                }
                position = GetVector(cPParam.positionVec.begin(),transitCheckPointCount);
                direction = GetVector(cPParam.directionVec.begin(), transitCheckPointCount);
            }
            return true;
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
int CheckPoint::GetTransitCheckPointCout()
{
    return transitCheckPointCount;
}
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




