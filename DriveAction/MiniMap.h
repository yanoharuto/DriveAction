#pragma once
#include <string>
#include "DxLib.h"
#include "ImgUI.h"
#include "PointUI.h"
#include "Utility.h"
class MiniMap
{
public:
    MiniMap();
    ~MiniMap();
    void Update(float playerPosX, float playerPosY);
    void Draw();
private:
    //プレイヤーのマーカーの色
    const unsigned int playerColor = GetColor(255,0,0);
    //マップのサイズ
    const float mapSize = 0.8f;
    //マーカーの速さ
    float markerSpeedX = 0.2f;
    float markerSpeedZ = 0.2f;
    const float mapStartPosX = -15.7f;
    const float mapStartPosZ = 10.0f;
    const float minimapEdgeX = 1350;
    const float minimapEdgeZ = 1350;
    int mapUINum = 0;
    int minimapX = SCREEN_WIDTH / 20 * 17;
    int minimapY = SCREEN_HEIGHT / 20 * 9.5f;
    int minimapWidth = 0;
    int minimapHeight = 0;

    //ミニマップの画像のアドレス
    const std::string miniMapAddress = "/Asset/CircuitMap.png";
    const float markerRadius = 15.0f;
    ImgUI* miniMap;
    PointUI* pointUI;
};