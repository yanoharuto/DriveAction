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
    markerBetweenScaleX = static_cast<float>(minimapWidth / 2) / minimapEdgeX * mapSize;
    markerBetweenScaleZ = static_cast<float>(minimapHeight / 2) / minimapEdgeZ * mapSize;
}

MiniMap::~MiniMap()
{
    SAFE_DELETE(miniMap);
    SAFE_DELETE(pointUI);
}

void MiniMap::Update(float playerPosX, float playerPosY)
{
    float x = minimapX + (playerPosX - mapStartPosX) * markerBetweenScaleX ;
    float y = minimapY + (playerPosY - mapStartPosZ) * markerBetweenScaleZ ;
    pointUI->SetXY(x, y);
}

void MiniMap::Draw()
{
    miniMap->DrawUI();
    pointUI->DrawUI();
}
