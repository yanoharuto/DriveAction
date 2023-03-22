#include "PlayerInformationCenter.h"

 std::unordered_map<Player*, PlayerRelatedInfo> PlayerInformationCenter::playerMap;
PlayerInformationCenter::PlayerInformationCenter()
{
}

PlayerInformationCenter::~PlayerInformationCenter()
{
    playerMap.clear();
}

void PlayerInformationCenter::AddPlayer(Player* player)
{
    playerMap.insert(std::make_pair(player, player->GetRelatedInfo()));
}

void PlayerInformationCenter::UpdatePlayerRelatedInfo()
{
    for (auto itr = playerMap.begin(); itr != playerMap.end(); itr++)
    {
        (*itr).second = (*itr).first->GetRelatedInfo();
    }
}

PlayerRelatedInfo PlayerInformationCenter::GetPlayerRelatedInfo(int num)
{
    auto ite = playerMap.begin();
    for (int i = 0; i < num; i++)
    {
        if (ite == playerMap.end())
        {
            ite = playerMap.begin();
        }
        ite++;
        if (i + 1 == num)
        {
            break;
        }
    }
    return (*ite).second;
}