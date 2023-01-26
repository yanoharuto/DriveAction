#include "MiniMap.h"
#include "UIManager.h"
#include "ImgUI.h"
#include "PointUI.h"
#include "Utility.h"
MiniMap::MiniMap(float mapPosX,float mapPosY,std::string mapGraphAddress)
{

    minimapX = mapPosX;
    minimapY = mapPosY;
    UIData uiData;
    uiData.x = mapPosX;
    uiData.y = mapPosY;
    uiData.dataHandle = LoadGraph(mapGraphAddress.c_str(), true);
    miniMap = new ImgUI(mapSize, uiData);
    pointUI = new PointUI(playerColor, uiData, markerRadius);
    GetGraphSize(uiData.dataHandle,&minimapWidth, &minimapHeight);
    float edgeX = minimapEdgeX;
    float edgeZ = minimapEdgeZ;
    markerBetweenScaleX = minimapWidth / 2 / edgeX * mapSize;
    markerBetweenScaleZ = minimapHeight / 2 / edgeZ * mapSize;
}

MiniMap::~MiniMap()
{
    SAFE_DELETE(miniMap);
    SAFE_DELETE(pointUI);
}

void MiniMap::Update(float playerPosX, float playerPosY)
{
    float x = minimapX + playerPosX * markerBetweenScaleX;
    float y = minimapY + playerPosY * markerBetweenScaleZ;
    pointUI->SetXY(x, y);
}

void MiniMap::Draw()
{
    miniMap->DrawUI();
    pointUI->DrawUI();
}
