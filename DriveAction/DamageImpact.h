#pragma once
#include <string>
#include "DamageObject.h"
/// <summary>
/// 飛び道具
/// </summary>
class DamageImpact:public DamageObject
{
public:
    DamageImpact();
    /// <summary>
    /// 車の位置から少し離れた所から出てくる
    /// </summary>
    /// <param name="carInfo"></param>
    DamageImpact(ItemArgumentCarInfo carInfo);
    ~DamageImpact();
    /// <summary>
    /// 移動と一定時間たつと消える
    /// </summary>
    /// <param name="deltaTime"></param>
    void Update(float deltaTime)override;
    /// <summary>
    /// 何かに当たったら壊れる
    /// </summary>
    void ConflictProccess() override;
private:
    //生存時間
    float aliveTime = 0;
    //最大生存時間
    const float setAliveTime = 12.0f;
    //移動速度
    const float speed = 400.0f;
    //当たり判定
    const float setRadius = 2.5f;
    //アセットのアドレス
    const std::string assetAddress = "data/model/Item/SpikeBall/SpikeBall.mv1";
};

