#pragma once
#include <unordered_map>
#include "UI.h"
#include "ItemTag.h"
class ItemUI :public UI
{

public:
    ItemUI() {};
    ItemUI(UIData data);
    void Update(ItemTag itemTag);
    void DrawUI()override;
private:
    int itemUIFrameGraphH;
    std::unordered_map<ItemTag,int> itemImgMap;
    const std::string accelation = "data/Accelation.png";
    const std::string hatena = "data/Hatena.png";
    const std::string rocket = "data/Rocket.png";
    const std::string spikeBall = "data/SpikeBall.png";
    const std::string itemUIFrame = "data/ItemUI.png";
};

