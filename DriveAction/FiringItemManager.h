#pragma once
#include <list>
#include <string>
#include "DamageObject.h"
#include "CircuitTrack.h"
#include "ItemArgumentCarInfo.h"
#include "ItemTag.h"
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
    void AddDamageObject(DamageObject* damageObj);
    /// <summary>
    /// 衝突
    /// </summary>
    /// <param name="conflictProccess"></param>
    void CircuitTrackConflictProccess(CircuitTrack* conflictProccess);
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name="deltaTime"></param>
    void Update(float deltaTime);
    /// <summary>
    /// 描画
    /// </summary>
    void Draw();
private:
    //オブジェクトタグがDamageObjectになってるオブジェクトのリスト
    std::list<DamageObject*> damageObjList;
};