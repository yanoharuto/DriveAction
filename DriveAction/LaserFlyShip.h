#pragma once
#include "FlyShip.h"
#include "PlayerRelatedInfo.h"
/// <summary>
/// レーザーを出す飛行船
/// </summary>
class LaserFlyShip abstract:
    public FlyShip
{
public:
    /// <summary>
    /// レーザーを出す船
    /// </summary>
    LaserFlyShip();
    /// <summary>
    /// 初期化 目的地の方に向かせる
    /// </summary>
    /// <param name="firstPos"></param>
    /// <param name="setDestinationPos"></param>
    LaserFlyShip(VECTOR firstPos, VECTOR setDestinationPos);
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~LaserFlyShip();
    /// <summary>
    /// カメラに映らなそうならエフェクトを消す
    /// </summary>
    /// <param name="playerInfo"></param>
    virtual void Init(PlayerRelatedInfo playerInfo);
    /// <summary>
    /// レーザーを照射
    /// </summary>
    virtual void GenerateLaser() = 0;
protected:
    //初期位置Y
    float firstPosY;
};
