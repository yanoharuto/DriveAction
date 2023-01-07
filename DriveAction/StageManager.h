#pragma once
#include "CircuitTrack.h"
#include "SkyDome.h"
#include <list>
/// <summary>
/// コースのロードや描画とか当たり判定とかする
/// </summary>
class StageManager
{
public:
    /// <summary>
    /// 
    /// </summary>
    /// <returns></returns>
    StageManager();

    ~StageManager();

    CircuitTrack* GetCircuit()const;
    std::string GetCheckPoint()const;
    void Draw()const;

private:
    CircuitTrack* circuit;
    SkyDome* skyDome;
    std::string checkPointAddres;
};