#include "MiniMap.h"
#include "UIManager.h"
#include "ImgUI.h"
#include "PointUI.h"
#include "CourceDataLoader.h"

MiniMap::MiniMap()
{
    UIData uiData;
    uiData.x = minimapX;
    uiData.y = minimapY;
    uiData.dataHandle = LoadGraph((CourceDataLoader::GetStageDataGenericAddress() + miniMapAddress).c_str(), true);
    miniMap = new ImgUI(mapSize, uiData);
    pointUI = new PointUI(playerColor, uiData, markerRadius);
    GetGraphSize(uiData.dataHandle,&minimapWidth, &minimapHeight);
    markerSpeedX = static_cast<float>(minimapWidth / 2) / minimapEdgeX * mapSize;
    markerSpeedZ = static_cast<float>(minimapHeight / 2) / minimapEdgeZ * mapSize;
}

MiniMap::~MiniMap()
{
    SAFE_DELETE(miniMap);
    SAFE_DELETE(pointUI);
}

void MiniMap::Update(float playerPosX, float playerPosY)
{
    float x = minimapX + (playerPosX - mapStartPosX) * markerSpeedX ;
    float y = minimapY + (playerPosY - mapStartPosZ) * markerSpeedZ ;
    pointUI->SetXY(x, y);
}

void MiniMap::Draw()
{
    miniMap->DrawUI();
    pointUI->DrawUI();
}
