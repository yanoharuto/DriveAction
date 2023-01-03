#pragma once
#include "Car.h"
#include <vector>
struct CircuitData
{
    //車が次に行くべき行き先が書いてある
    std::vector<VECTOR> positionVec;
    //逆走してゴールしないように方向も乗せる
    std::vector<VECTOR> directionVec;
    //何週したらゴールなのか
    int goalRoundNum = 0;
};
/// <summary>
/// プレイヤーが何回ゴールしたか数える
/// </summary>
class CheckPoint final:
    public Object
{
public:
    CheckPoint();
    /// <summary>
   /// コース情報得するよ
   /// </summary>
   /// <param name="roundNum">何週走るか</param>
   /// <param name="fileName">どのファイルから所得するか</param>
   /// <returns></returns>
    CheckPoint(const int roundNum,const TCHAR* fileName);
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
    /// <param name="car"></param>
    void Update(Car* car);
    /// <summary>
    /// 他のCPUにもコピーさせるために渡す
    /// </summary>
    /// <returns></returns>
    CircuitData GetCheckPoint() const;
private:
    /// <summary>
    /// 初期化処理
    /// </summary>
    void InitMember();
    CircuitData cPParam;
    //positionからこれだけ近かったらゴール
    const float goalRadius = 80.0f;
    //車はDirと反対向きなので内積を取って1に近かったらゴールした判定
    const float dirJugeLine = 0.8f;
    //ゴールされた回数
    int goalNum = 0;
    //ベクター配列のサイズ
    int vecSize = 0;

};

