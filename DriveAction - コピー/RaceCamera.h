#pragma once
#include "DxLib.h"
#include "PlaySceneCamaeraArgumentInfo.h"
//プレイヤークラスの前方宣言
class RaceCamera final
{
public:
    RaceCamera();
    ~RaceCamera();

    void Update(PlaySceneCameraArgumentInfo argumentInfo, float deltaTime);
    void Update(float deltaTime);
private:
    //カメラの位置
    VECTOR position = {};
    //カメラの向き
    VECTOR direction = {};
    //プレイヤーまでの距離Y
    const float betweenPlayerY = 11.0f;
    //プレイヤーまでの距離X
    const float betweenPlayerX = 24.0f;
    //プレイヤーまでの距離Z
    const float betweenPlayerZ = 24.0f;
    //描画しようとする範囲
    const float setNearValue = 0.1f;
    //描画しようとする範囲
    const float setFarValue = 6000.0f;
    //カメラの狙う先までの距離の大きさ
    const float aimBetween = 30.0f;
    //カメラが車の方に向く速度
    const float cameraRotateSpeed = 3.2f;
};

