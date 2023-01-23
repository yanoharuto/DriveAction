#pragma once
#include <vector>
#include "ConflictExamineResultInfo.h"
#include "CircuitDataStruct.h"
/// <summary>
/// プレイヤーが何回ゴールしたか数える
/// </summary>
class CheckPoint final:
    public Object
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
    bool CheckPointUpdate(const ConflictExamineResultInfo carInfo);
    /// <summary>
    /// 他のCPUにもコピーさせるために渡す
    /// </summary>
    /// <returns></returns>
    CircuitData GetCheckPoint() const;
    /// <summary>
    /// ゴールした回数を返す
    /// </summary>
    /// <returns></returns>
    int GetGoalCount();
    int GetTransitCheckPointCount();
    /// <summary>
    /// チェックポイントまでの差を出す
    /// </summary>
    /// <returns>チェックポイントまでの差</returns>
    float GetCheckPointDistance();
private:

    /// <summary>
    /// 初期化処理
    /// </summary>
    void InitMember();
    //サーキットのデータ
    CircuitData cPParam;
    //positionからこれだけ近かったらゴール
    const float goalRadius = 120.0f;
    //車はDirと反対向きなので内積を取って1に近かったらゴールした判定
    const float dirJugeLine = 0.8f;
    //チェックポイントのベクターを調べる回数
    const int vectorExamineCount = 10;
    //通過した回数
    int transitCheckPointCount = 0;
    //ゴールした回数
    int goalCount = 0;
    //ベクター配列のサイズ
    int vecSize = 0;
    //チェックポイントまでの差
    float checkPointDistance;
};

