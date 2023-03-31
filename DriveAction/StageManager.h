#pragma once
#include "CircuitTrack.h"
#include "SkyDome.h"
#include <list>
class CourceDataLoader;
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
    void Update();
    CircuitTrack* GetCircuit()const;
    void Draw()const;

private:
    CircuitTrack* circuit;
    SkyDome* skyDome;
};