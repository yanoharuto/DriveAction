#pragma once
#include <vector>
#include "DataAddresLoader.h"
class RankingData
{
public:
    RankingData();

    ~RankingData();
    void UpdateRanking(int score);
private:
    std::vector<int> scoreRanking;
    
};