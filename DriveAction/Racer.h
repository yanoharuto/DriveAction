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
    Racer(CircuitData circuitData);
    virtual ~Racer();
    /// <summary>
    /// 車を走らせたりアイテムを使ったりする
    /// </summary>
    /// <param name="deltaTime"></param>
    /// <param name="outsideHitFlag"></param>
    /// <param name="damageObj"></param>
    virtual void Update(float deltaTime,bool outsideHitFlag,DamageObjectGenerator* damageObj);
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
    /// 衝突処理
    /// </summary>
    /// <param name="conflictResultInfo"></param>
    /// <param name="deltaTime"></param>
    void ConflictProcces(ConflictExamineResultInfo conflictResultInfo,float deltaTime);
    /// <summary>
    /// 当たり判定を調べるために必要な情報
    /// </summary>
    /// <returns></returns>
    HitCheckExamineObjectInfo GetCarHitCheckExamineInfo();
    /// <summary>
    /// 当たった場合返す情報
    /// </summary>
    /// <returns></returns>
    ConflictExamineResultInfo GetConflictExamineResultInfo();
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
    /// 共通処理
    /// </summary>
    /// <param name="deltaTime"></param>
    /// <param name="outsideHitFlag"></param>
    /// <param name="damageObj"></param>
    void CommonUpdate(float deltaTime, bool outsideHitFlag,DamageObjectGenerator* damageObj);
    /// <summary>
    /// インストラクタで呼ぶ
    /// </summary>
    /// <param name="car"></param>
    void SetCarPointer(Car* car);
    //順位
    int rank;
    //通ってきたチェックポイント
    CheckPoint* checkPoint;
    //車
    Car* car;
    //音
    SoundPlayer* soundPlayer;
    //アイテムを取ってきて保存する
    ItemHolder* itemHolder;
};

