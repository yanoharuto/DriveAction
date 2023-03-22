#pragma once
#include "CircuitDataStruct.h"
#include "SoundPlayer.h"
#include "ItemHolder.h"
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
    virtual void Update(float deltaTime);
    /// <summary>
    /// このレーサーの車に引数のオブジェクトがぶつかっているか調べる
    /// </summary>
    /// <param name="objInfo"></param>
    /// <returns></returns>
    bool HitCheck(HitCheckExamineObjectInfo objInfo);
    /// <summary>
    /// 描画する
    /// </summary>
    void Draw();
    /// <summary>
    /// 当たり判定を調べるために必要な情報
    /// </summary>
    /// <returns></returns>
    HitCheckExamineObjectInfo GetCarHitCheckExamineInfo();

    /// <summary>
    /// ランク
    /// </summary>
    int* GetRankPointer();
    /// <summary>
    /// チェックポイントを返す
    /// </summary>
    CheckPoint* GetCheckPointer();

protected:
    /// <summary>
    /// インストラクタで呼ぶ
    /// </summary>
    /// <param name="car"></param>
    void SetCarPointer(Car* car);

    int transitCPCount = 0;

    bool reverse = false;
    //順位
    int rank;
    //通ってきたチェックポイント
    CheckPoint* checkPoint;
    //車
    Car* car;
    //アイテムを取ってきて保存する
    ItemHolder* itemHolder;
    float hp = 0;
};

