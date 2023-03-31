#pragma once
#include <vector>
#include "ConflictExamineResultInfo.h"

#include "HitCheckExamineObjectInfo.h"
#include "Actor.h"
/// <summary>
/// プレイヤーが何回ゴールしたか数える
/// </summary>
class CheckPoint final
{
public:
    CheckPoint();
    //デストラクタ
    ~CheckPoint();
    /// <summary>
    /// チェックポイントを通過したか調べる
    /// </summary>
    /// <param name="carInfo">ぶつかったか調べる車</param>
    bool IsTransitCheckPoint(int transitCount, const HitCheckExamineObjectInfo carInfo);
    /// <summary>
    /// チェックポイントまでの差を出す
    /// </summary>
    /// <returns>チェックポイントまでの差</returns>
    float GetCheckPointDistance(int transitCount,VECTOR objPos);
    /// <summary>
    /// 通過回数は何回ゴールしたことなのか返す
    /// </summary>
    /// <param name="transitCount"></param>
    /// <returns></returns>
    int GetGoalCount(int transitCount);
    VECTOR GetCheckPointPos(int transitCount);
    VECTOR GetCheckPointDir(int transitCount);
private:
    /// <summary>
/// チェックポイントに車が通過したか判定する
/// </summary>
/// <param name="pos"></param>
/// <param name="dir"></param>
/// <param name="carPos"></param>
/// <returns></returns>
    bool IsTransitCheckPointCar(VECTOR pos, VECTOR dir, VECTOR carPos);

    //ベクター配列のサイズ
    int vecSize = 0;
    //ゴールまでの道のりテキスト
    const std::string checkPointPosPass = "/CourcePos.txt";
    //ゴールまでの道のりテキスト
    const std::string checkPointDirPass = "/CourceDir.txt";
};

