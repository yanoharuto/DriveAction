#pragma once
#include "CircuitDataStruct.h"
#include "SoundPlayer.h"
#include "Car.h"
#include "CheckPoint.h"
#include "ConflictExamineResultInfo.h"
#include "DamageObjectGenerator.h"
/// <summary>
/// レーサー　現状　コンピューターとプレイヤーの二種類
/// </summary>
class Racer abstract
{
public:
    Racer();
    virtual ~Racer();
    /// <summary>
    /// 車を走らせたりアイテムを使ったりする
    /// </summary>
    /// <param name="deltaTime"></param>
    /// <param name="outsideHitFlag"></param>
    /// <param name="damageObj"></param>
    virtual void Update();
    /// <summary>
    /// 描画する
    /// </summary>
    void Draw();
    /// <summary>
    /// 発進前に上下に動く
    /// </summary>
    void UpDown();
    /// <summary>
    /// ランク
    /// </summary>
    int* GetRankPointer();
    /// <summary>
    /// チェックポイントを返す
    /// </summary>
    CheckPoint* GetCheckPointer();

protected:

    int transitCPCount = 0;

    bool reverse = false;
    //順位
    int rank;
    //通ってきたチェックポイント
    CheckPoint* checkPoint;
    //車
    Car* car;
};

