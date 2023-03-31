#include "MiniMap.h"
#include "UIManager.h"
#include "ImgUI.h"
#include "PointUI.h"
#include "CourceDataLoader.h"

MiniMap::MiniMap()
{
    icon.x = miniMapUpLeftX + mapRength;
    icon.y = miniMapUpLeftY + mapRength;
    miniMap.dataHandle = LoadGraph(miniMapPass.c_str(), true);
    
    GetGraphSize(miniMap.dataHandle,&mapGraphWidth, &mapGraphHeight);


}

MiniMap::~MiniMap()
{
}

void MiniMap::Update(ObjInfo objInfo, std::list<VECTOR> setCoinPosList)
{
    VECTOR pos = ConvertPosition(objInfo.pos);
    miniMap.x = pos.x;
    miniMap.y = pos.y;
    coinPosList.clear();
    for (auto ite = setCoinPosList.begin(); ite != setCoinPosList.end(); ite++)
    {
        pos = ConvertPosition((*ite));
        coinPosList.push_back(pos);
    }
}

void MiniMap::Draw()
{
    DrawRotaGraph(icon.x,icon.y,1,0,miniMap.dataHandle,false);
    DrawCircle(miniMap.x, miniMap.y, iconSize ,playerColor, 1, 1);
    for (auto ite = coinPosList.begin(); ite != coinPosList.end(); ite++)
    {
        DrawCircle((*ite).x, (*ite).y, iconSize, coinColor, 1, 1);
    }
}

VECTOR MiniMap::ConvertPosition(VECTOR pos)
{
    VECTOR data;
    data.x = -pos.x * (mapGraphWidth / 2) / 6000 + miniMapFrontX ;

    data.y = pos.z * (mapGraphHeight / 2) / 6000 + miniMapFrontY;
    return data;
}
