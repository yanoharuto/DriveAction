#pragma once
#include <string>
#include "DxLib.h"
#include "UIDataStruct.h"
#include "UIManager.h"

class MiniMap
{
public:
    MiniMap(UIManager* uiManager, float mapPosX, float mapPosY, std::string mapGraphAddress);
    MiniMap() {
    };
    ~MiniMap();
    void Update(UIManager* uiManager, float playerPosX, float playerPosY);
private:
    const unsigned int playerColor = GetColor(255,0,0);
    int playerMarkerUINum = 0;
    const float mapSize = 0.4f;
    const float markerSize = 0.1f;
    const int courceModelStartPosX = -12;
    const int courceModelStartPosY = -12;
    int mapUINum = 0;
    int minimapX = 0;
    int minimapY = 0;

    const float markerRadius = 5.75f;
    UIData uiData = {};
};

