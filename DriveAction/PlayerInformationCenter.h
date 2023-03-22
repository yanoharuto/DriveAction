#pragma once
#include <unordered_map>
#include "DxLib.h"
#include "PlayerRelatedInfo.h"
#include "Player.h"
class PlayerInformationCenter
{
public:
    PlayerInformationCenter();
    ~PlayerInformationCenter();
    void AddPlayer(Player* player);
    void UpdatePlayerRelatedInfo();
    static PlayerRelatedInfo GetPlayerRelatedInfo(int num);
private:
   static std::unordered_map<Player*, PlayerRelatedInfo> playerMap;
};

