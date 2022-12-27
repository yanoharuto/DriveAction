#pragma once
#include "Stage.h"
#include <vector>
/// <summary>
/// プレイヤーが何回ゴールしたか数える
/// </summary>
class Goal :
    public Stage
{
public:
    Goal(const int roundNum);
    ~Goal();
    /// <summary>
    /// プレイヤーがぶつかったら次の行き先を設定する
    /// </summary>
    /// <param name="actor"></param>
    void ConflictProcess(Actor* actor)override;
private:
    //車が次に行くべき行き先が書いてある
    std::vector<VECTOR> positionVec;
    //逆走してゴールしないように方向も乗せる
    std::vector<VECTOR> directionVec;
    //positionからこれだけ近かったらゴール
    const float goalRadius = 80.0f;
    //車はDirと反対向きなので内積を取って1に近かったらゴールした判定
    const float dirJugeLine = 0.8f;
    //ゴールされた回数
    int goalNum = 0;
    //ベクター配列のサイズ
    int vecSize = 0;
    //何週したらゴールなのか
    int goalRoundNum = 0;
    //directionVecから貰ったデータを入れる
    VECTOR direction;
};

