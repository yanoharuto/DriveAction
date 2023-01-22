#include "MiniMap.h"
#include "UIManager.h"
#include "ImgUI.h"
#include "PointUI.h"
#include "Utility.h"
MiniMap::MiniMap(float mapPosX,float mapPosY,std::string mapGraphAddress)
{
    UIData uiData;
    minimapX = mapPosX;
    minimapY = mapPosY;
    uiData.x = mapPosX;
    uiData.y = mapPosY;
    uiData.dataHandle = LoadGraph(mapGraphAddress.c_str(), true);
    miniMap = new ImgUI(mapSize, uiData);


    pointUI = new PointUI(playerColor,uiData,markerRadius);
}

MiniMap::~MiniMap()
{
    SAFE_DELETE(miniMap);
    SAFE_DELETE(pointUI);
}

void MiniMap::Update(float playerPosX, float playerPosY)
{
    float x = minimapX + courceModelStartPosX + playerPosX  * markerSize ;
    float y = minimapY + courceModelStartPosY + playerPosY * markerSize ;
    pointUI->SetXY(x, y);
}

void MiniMap::Draw()
{
    miniMap->DrawUI();
    pointUI->DrawUI();
}
