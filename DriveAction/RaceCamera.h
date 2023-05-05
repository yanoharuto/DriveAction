#pragma once
#include "DxLib.h"
#include <vector>
class ObjectObserver;
class ObjectSubject;
class RacerManager;
class RaceCamera final
{
public:
    RaceCamera(RacerManager* manager);
    ~RaceCamera();
    void Update();
private:
    //カメラの位置
    VECTOR position = {};
    //カメラの向き
    VECTOR direction = {};
    //プレイヤーまでの距離Y
    const float betweenPlayerY = 50.0f;
    //プレイヤーまでの距離X
    const float betweenPlayerX = 370.0f;
    //プレイヤーまでの距離Z
    const float betweenPlayerZ = 370.0f;
    //描画しようとする範囲
    const float setNearValue = 15.0f;
    //描画しようとする範囲
    const float setFarValue = 10700.0f;
    //カメラの狙う先までの距離の大きさ
    const float aimBetween = 30.0f;
    //カメラが車の方に向く速度
    const float cameraRotateSpeed = 0.043f;
    //プレイヤーの位置を教えてくれるやつ
    std::vector<ObjectObserver*> playerObserverVec;
};

