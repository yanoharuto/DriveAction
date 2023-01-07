#include "CheckPoint.h"
#include "VECTOR3Loader.h"
#include "HitChecker.h"
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
/// コース情報得するよ
/// </summary>
/// <param name="roundNum">何週走るか</param>
/// <param name="fileName">どのファイルから所得するか</param>
/// <returns></returns>
CheckPoint::CheckPoint(const TCHAR* fileName)
{
    VECTOR3Loader loader;
    loader.LoadCheckPoint(&cPParam.positionVec,&cPParam.directionVec, fileName);
    InitMember();
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
void CheckPoint::Update(ArgumentConflictInfo carInfo)
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
                if (transitCheckPointCount < cPParam.positionVec.size())
                {
                    transitCheckPointCount = 0;
                }
                position = cPParam.positionVec[transitCheckPointCount];
                direction = cPParam.directionVec[transitCheckPointCount];
            }
            break;
        }
    }
    //最後に目標地点までどのぐらい離れてるか返す
    checkPointDistance = VSize(VSub(position,carInfo.pos));
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
int CheckPoint::GetCheckPointDistance()
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




