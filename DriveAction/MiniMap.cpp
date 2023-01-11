#include "MiniMap.h"
#include "UIManager.h"
#include "ImgUI.h"
#include "PointUI.h"
MiniMap::MiniMap(UIManager* uiManager, float mapPosX,float mapPosY,std::string mapGraphAddress)
{
    minimapX = mapPosX;
    minimapY = mapPosY;
    uiData.x = mapPosX;
    uiData.y = mapPosY;
    uiData.dataHandle = LoadGraph(mapGraphAddress.c_str(), true);
    ImgUI* miniMap = new ImgUI(mapSize, uiData);
    mapUINum = uiManager->AddUI(miniMap);

    PointUI* pointUI = new PointUI(playerColor,uiData,markerRadius);
    playerMarkerUINum = uiManager->AddUI(pointUI);
}

MiniMap::~MiniMap()
{
}

void MiniMap::Update(UIManager* uiManager, float playerPosX, float playerPosY)
{
    float x = minimapX + courceModelStartPosX + playerPosX  * markerSize ;
    float y = minimapY + courceModelStartPosY + playerPosY * markerSize ;
    uiManager->Update(playerMarkerUINum,x,y);
#ifdef _DEBUG
  //  printfDx("miniMap::%f,%f\n",x,y);
#endif // !_DEBUG

    
}
