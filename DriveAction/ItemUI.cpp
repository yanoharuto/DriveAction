#include "ItemUI.h"
#include "DxLib.h"
ItemUI::ItemUI(UIData data)
{
    itemImgMap.insert(std::make_pair(ItemTag::accelerator, LoadGraph(accelation.c_str())));
    itemImgMap.insert(std::make_pair(ItemTag::attack, LoadGraph(spikeBall.c_str())));
    itemImgMap.insert(std::make_pair(ItemTag::kite, LoadGraph(rocket.c_str())));
    itemImgMap.insert(std::make_pair(ItemTag::roulette, LoadGraph(hatena.c_str())));
    uiData = data;
    uiData.dataHandle = itemImgMap[ItemTag::roulette];
    itemUIFrameGraphH = LoadGraph(itemUIFrame.c_str());
}
void ItemUI::Update(ItemTag itemTag)
{
    uiData.dataHandle = itemImgMap[itemTag];
}

void ItemUI::DrawUI()
{
    DrawRotaGraph(uiData.x, uiData.y, 0.3, 0, uiData.dataHandle, true);
    DrawRotaGraph(uiData.x, uiData.y, 0.3, 0, itemUIFrameGraphH, true);
}
