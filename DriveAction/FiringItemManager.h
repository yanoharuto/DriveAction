#pragma once
#include <list>
#include "CircuitTrack.h"
#include "DamageObjectGenerator.h"
/// <summary>
/// 飛び道具の面倒を見る奴
/// </summary>
class FiringItemManager
{
public:

    /// <summary>
    /// 生成したときに追加する
    /// </summary>
    /// <param name="conflictProcesser"></param>
    FiringItemManager();
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~FiringItemManager();
    /// <summary>
    /// 投擲アイテムを追加
    /// </summary>
    /// <param name="itemTag"></param>
    /// <param name="carInfo"></param>
    static void AddFiringObject(Actor* damageObj);
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name="deltaTime"></param>
    void Update();
    /// <summary>
    /// 描画
    /// </summary>
    void Draw();
private:
    DamageObjectGenerator* damageObjGenerator;

    //オブジェクトタグがDamageObjectになってるオブジェクトのリスト
    static std::list<Actor*> damageObjList;
};