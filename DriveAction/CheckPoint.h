#pragma once
#include <vector>
#include "ConflictExamineResultInfo.h"
#include "CircuitDataStruct.h"
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

    /// <summary>
    /// コース情報複製用
    /// </summary>
    /// <param name="checkPointParam"></param>
    /// <returns></returns>
    CheckPoint(const CircuitData circuitData);
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

    //サーキットのデータ
    CircuitData cPParam;
    //positionからこれだけ近かったらゴール
    const float goalTapeHalfLength = 70.0f;
    //次のチェックポイントまでの向きを出し始める範囲
    const float goalRadius = 55.0f;
    //車はDirと反対向きなので内積を取って1に近かったらゴールした判定
    const float dirJugeLine = 0.8f;
    //チェックポイントのベクターを調べる回数
    const int checkPointExamineCount = 4;
    //通過した回数
    int transitCheckPointCount = 0;
    //ゴールした回数
    int goalCount = 0;
    //ベクター配列のサイズ
    int vecSize = 0;
    //チェックポイントまでの差
    float checkPointDistance;
};

