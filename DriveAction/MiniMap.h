#pragma once
#include <string>
#include <list>
#include "DxLib.h"
#include "UIDataStruct.h"
#include "Utility.h"
#include "ObjPosAndDir.h"
class MiniMap
{
public:
    MiniMap();
    ~MiniMap();
    void Update(ObjInfo objInfo,std::list<VECTOR> setCoinPosList);
    void Draw();
private:
    VECTOR ConvertPosition(VECTOR pos);
    //プレイヤーのマーカーの色
    const unsigned int playerColor = GetColor(255,0,0);
    //収集物の色
    const unsigned int coinColor = GetColor(200,0,200);
    //マップの幅
    const float mapRength = 100.0f;
    //mapの描画中心座標
    const int miniMapFrontX = UI_SCREEN_WIDTH * 17;
    //mapの描画中心座標
    const int miniMapFrontY = UI_SCREEN_HEIGHT * 13;
    //描画開始左上X座標
    const int miniMapUpLeftX = miniMapFrontX - mapRength;
    //描画開始左上Y座標
    const int miniMapUpLeftY = miniMapFrontY - mapRength;
    
    //ミニマップの画像の横幅
    int mapGraphWidth = 0;
    //ミニマップの画像の縦幅
    int mapGraphHeight = 0;

    //ミニマップの画像のアドレス
    const std::string miniMapPass = "data/miniMap.png";
    //自機のIconの大きさ
    const float iconSize = 5.0f;
    //ミニマップ
    UIData miniMap;
    //自機のアイコン
    UIData icon;

    std::list<VECTOR> coinPosList;
};