#include "Goal.h"
#include "DestinationLoader.h"

/// <summary>
/// デフォルトコンストラクタ
/// </summary>
/// <returns></returns>
Goal::Goal()
{
    direction = {};
    cPParam.goalRoundNum = 0;
    vecSize = 0;
}
/// <summary>
/// コース情報得するよ
/// </summary>
/// <param name="roundNum">何週走るか</param>
/// <param name="fileName">どのファイルから所得するか</param>
/// <returns></returns>
Goal::Goal(const int roundNum, const TCHAR* fileName)
{
    DestinationLoader loader;
    loader.LoadDestination(&cPParam.positionVec,&cPParam.directionVec, fileName);
    cPParam.goalRoundNum = roundNum;
    InitMember();
}
/// <summary>
/// コース情報複製用
/// </summary>
/// <param name="checkPointParam"></param>
/// <returns></returns>
Goal::Goal(const CircuitData circuitData)
{
    cPParam = circuitData;
    InitMember();
}

Goal::~Goal()
{
}

/// <summary>
/// プレイヤーがぶつかったら次の行き先を設定する
/// </summary>
/// <param name="car"></param>
void Goal::Update(Car* car)
{
    if (car->GetTag() == ObjectTag::car)
    {
        float theta = VDot(car->GetDir(), direction);
        //ぶつかった相手が逆走してなかったら次のチェックポイントに行く
        if (theta > dirJugeLine)
        {
            goalNum++;
            //チェックポイント通過が一週分ならお役御免
            if (goalNum / vecSize == cPParam.goalRoundNum)
            {
                aliveFlag = false;
            }
            else
            {
                //それ以外なら位置更新
                position = cPParam.positionVec[goalNum % vecSize];
                direction = cPParam.directionVec[goalNum % vecSize];
            }
        }
    }
}

/// <summary>
/// 他のCPUにもコピーさせるために渡す
/// </summary>
/// <returns></returns>
CircuitData Goal::GetCheckPoint() const 
{
    return cPParam;
};
/// <summary>
/// 初期化処理
/// </summary>
void Goal::InitMember()
{
    tag = ObjectTag::goal;
    position = cPParam.positionVec.front();
    direction = cPParam.directionVec.front();
    radius = goalRadius;
    vecSize = cPParam.positionVec.size();
}




