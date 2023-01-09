#pragma once
#include "Car.h"
#include <vector>
#include "ArgumentObjInfoStruct.h"
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
    bool CheckPointUpdate(const ArgumentConflictInfo carInfo);
    /// <summary>
    /// 他のCPUにもコピーさせるために渡す
    /// </summary>
    /// <returns></returns>
    CircuitData GetCheckPoint() const;
    /// <summary>
    /// チェックポイント通過回数を返す
    /// </summary>
    /// <returns>チェックポイント通過回数</returns>
    int GetTransitCheckPointCout();
    /// <summary>
    /// チェックポイントまでの差を出す
    /// </summary>
    /// <returns>チェックポイントまでの差</returns>
    float GetCheckPointDistance();
private:
    VECTOR GetVector (std::list<VECTOR>::iterator listIte,int count)
    {
        for (int i = 0; i < count; i++)
        {
            listIte++;
        }
        return *listIte;
    }
    /// <summary>
    /// 初期化処理
    /// </summary>
    void InitMember();
    //サーキットのデータ
    CircuitData cPParam;
    //positionからこれだけ近かったらゴール
    const float goalRadius = 80.0f;
    //車はDirと反対向きなので内積を取って1に近かったらゴールした判定
    const float dirJugeLine = 0.8f;
    //チェックポイントのベクターを調べる回数
    const int vectorExamineCount = 5;
    //通過した回数
    int transitCheckPointCount = 0;
    //ベクター配列のサイズ
    int vecSize = 0;
    //チェックポイントまでの差
    float checkPointDistance;
};

