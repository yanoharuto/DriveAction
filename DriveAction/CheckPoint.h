#pragma once
#include <vector>
#include "ConflictExamineResultInfo.h"

#include "HitCheckExamineObjectInfo.h"
#include "Actor.h"
/// <summary>
/// プレイヤーが何回ゴールしたか数える
/// </summary>
class CheckPoint final:
    public Actor
{
public:
    CheckPoint();
    //デストラクタ
    ~CheckPoint();
    /// <summary>
    /// プレイヤーがぶつかったら次の行き先を設定する
    /// </summary>
    /// <param name="carInfo">ぶつかったか調べる車</param>
    ConflictExamineResultInfo CheckPointUpdate(const HitCheckExamineObjectInfo carInfo);
    /// <summary>
    /// チェックポイントに車が通過したか判定する
    /// </summary>
    /// <param name="pos"></param>
    /// <param name="dir"></param>
    /// <param name="carPos"></param>
    /// <returns></returns>
    bool IsTransitCheckPointCar(VECTOR pos,VECTOR dir,VECTOR carPos);
    VECTOR GetLastPos();
    VECTOR GetLastDir();

    /// <summary>
    /// ゴールした回数を返す
    /// </summary>
    /// <returns></returns>
    int GetGoalCount();
    //チェックポイントに通過した回数を返す
    int GetTransitCheckPointCount();
    /// <summary>
    /// チェックポイントまでの差を出す
    /// </summary>
    /// <returns>チェックポイントまでの差</returns>
    float GetCheckPointDistance();
    bool HitCheckConflict(HitCheckExamineObjectInfo objInfo) override;
private:
    //通過した回数
    int transitCount = 0;
    //ゴールした回数
    int goalCount = 0;
    //ベクター配列のサイズ
    int vecSize = 0;
    //チェックポイントまでの差
    float checkPointDistance;
};

