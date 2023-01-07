#pragma once
#include <string>
/// <summary>
/// ステージのデータのアドレス
/// </summary>
struct StageDataAddress
{
    const std::string cFirstPosition = "firstPosition.txt";//初期位置が書いてあるテキスト
    const std::string cGoalStatus = "goalStatus.txt";//ゴールまでの道のりテキスト
    const std::string cStageAddress = "stageModeleAddress.txt";//ステージのアセットたちのアドレス　3つに分かれる
};