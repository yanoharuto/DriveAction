#pragma once
#include <list>
#include "ObjectObserver.h"
class Timer;
class BomberFlyShip;
class CircleLaserFlyShip;
class UpDownLaserFlyShip;
class RacerManager;
/// <summary>
/// 敵機のマネージャー
/// </summary>
class FlyShipManager
{
public:
    /// <summary>
    /// 敵機の初期化する
    /// </summary>
    FlyShipManager(RacerManager* racerManager);

    ~FlyShipManager();
    /// <summary>
    /// 敵機たちの更新
    /// </summary>
    /// <param name="infoCenter"></param>
    void Update();
    /// <summary>
    /// 描画
    /// </summary>
    void Draw();
    /// <summary>
    /// 爆撃機の初期化
    /// </summary>
    /// <param name="infoCenter"></param>
    void BomberShipInit();
    /// <summary>
    /// レーザーシップの初期化
    /// </summary>
    /// <param name="infoCenter"></param>
    void LaserShipInit();
private:
    //爆撃機のリスト
    std::list<BomberFlyShip*>bombList;
    //円環上に陣形を作る敵機のリスト
    std::list<CircleLaserFlyShip*>circleFlyshipList;
    //上下に移動しながらレーザーを発射する敵機のリスト
    std::list<UpDownLaserFlyShip*>updownFlyShipList;
    //爆撃機再利用のタイマー
    Timer* bomberFlyShipGoTimer;
    //プレイヤーの位置
    ObjectObserver* playerObserver;
    //爆撃機の初期化の間隔
    const float setBShipInitSpan = 5.0f;
    //円状の敵機の数
    const int circleShipNum = 6;
    //一度に発進する敵機の数
    const int BomberFlyShipNum = 3;
    //爆撃機の初期化するときに使う角度
    const int bShipInitRandDeg = 60;
    //爆撃機の初期化時のプレイヤーとの距離に使う
    const float initBShipGeneratePosScale = 1000.0f;
    //爆撃機同士の距離
    const float initBShipBetween = 300.0f;
    //レーザー売ってくる敵の座標
    const std::string enemyPosPass = "data/stageMap_enemyPos.csv";    
};