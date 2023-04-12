#include "MiniMap.h"
#include "UIManager.h"
#include "ImgUI.h"
#include "PointUI.h"
#include "CourceDataLoader.h"
#include "OriginalMath.h"
MiniMap::MiniMap()
{
    icon.x = miniMapUpLeftX + mapRength;
    icon.y = miniMapUpLeftY + mapRength;
    miniMap.dataHandle = LoadGraph(miniMapPass.c_str(), true);
    
    GetGraphSize(miniMap.dataHandle,&mapGraphWidth, &mapGraphHeight);

    mapSizeCoefficient = mapSize / mapGraphWidth;
}

MiniMap::~MiniMap()
{
}

void MiniMap::Update(ObjInfo objInfo, std::list<VECTOR> setCollectPos)
{
    mapRotate = OriginalMath::GetDegreeMisalignment(VGet(1, 0, 0), objInfo.dir) * RAGE;
    mapRotate = VCross(VGet(1, 0, 0), objInfo.dir).y < 0 ? -mapRotate: mapRotate;
    coinPosList.clear();
    for (auto ite = setCollectPos.begin(); ite != setCollectPos.end(); ite++)
    {
        VECTOR collectPos = *ite;
        collectPos.y = 0;

        VECTOR playerPos = objInfo.pos;
        playerPos.y = 0;
        collectPos = VSub(collectPos, playerPos);
        if (VSize(collectPos) < mapGraphWidth)
        {
            OriginalMath::GetYRotateVector(collectPos, mapRotate);
            collectPos = ConvertPosition(collectPos);
            coinPosList.push_back(collectPos);
        }
    }
}

void MiniMap::Draw()
{
    DrawRotaGraph(icon.x, icon.y, mapSizeCoefficient, mapRotate, miniMap.dataHandle, true);
    DrawCircle(icon.x, icon.y, iconSize, playerColor, 1, 1);
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
