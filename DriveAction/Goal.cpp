#include "Goal.h"
#include "DestinationLoader.h"

Goal::Goal()
{
    direction = {};
    goalRoundNum = 0;
    vecSize = 0;
}

Goal::Goal(const int roundNum, const TCHAR* fileName)
{
    DestinationLoader loader;
    loader.LoadDestination(&positionVec,&directionVec, fileName);
    tag = ObjectTag::goal;
    goalRoundNum = roundNum;
    position = positionVec.front();
    direction = directionVec.front();
    radius = goalRadius;
    vecSize = positionVec.size();
}

Goal::~Goal()
{
}

/// <summary>
/// プレイヤーがぶつかったら次の行き先を設定する
/// </summary>
/// <param name="actor"></param>
void Goal::ConflictProcess(Actor* actor)
{
    if (actor->GetTag() == ObjectTag::player)
    {
        float theta = VDot(actor->GetDir(), direction);
        //ぶつかった相手が逆走してなかったら次のチェックポイントに行く
        if (theta > dirJugeLine)
        {
            goalNum++;
            //チェックポイント通過が一週分ならお役御免
            if (goalNum / vecSize == goalRoundNum)
            {
                aliveFlag = false;
            }
            else
            {
                //それ以外なら位置更新
                position = positionVec[goalNum % vecSize];
                direction = directionVec[goalNum % vecSize];
            }
        }
    }
}




