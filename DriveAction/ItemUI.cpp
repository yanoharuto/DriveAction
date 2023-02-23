#include "ItemUI.h"
#include "DxLib.h"
ItemUI::ItemUI(UIData data)
{
    itemImgMap[0] = LoadGraph(accelation.c_str());
    itemImgMap[1] = LoadGraph(spikeBall.c_str());
    itemImgMap[2] = LoadGraph(rocket.c_str());
    itemImgMap[3] = LoadGraph(hatena.c_str());
    uiData = data;
    uiData.dataHandle = itemImgMap[ItemTag::roulette];
    itemUIFrameGraphH = LoadGraph(itemUIFrame.c_str());
}
ItemUI::~ItemUI()
{
    for(int i = 0; i < ItemTag::non; i++)
    {
        DeleteGraph(itemImgMap[i]);
    }
    DeleteGraph(itemUIFrameGraphH);
}
void ItemUI::Update(ItemTag itemTag)
{
    uiData.dataHandle = itemImgMap[itemTag];
}

void ItemUI::DrawUI()
{
    DrawRotaGraph(uiData.x, uiData.y, graphSize, 0, uiData.dataHandle, true);
    DrawRotaGraph(uiData.x, uiData.y, graphSize, 0, itemUIFrameGraphH, true);
}
