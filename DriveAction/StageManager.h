#pragma once
#include "CircuitTrack.h"
#include "SkyDome.h"
#include "CircuitDataLoader.h"
class StageManager
{
public:
    StageManager()
    {
        circuit = nullptr;
        skyDome = nullptr;
    };
    StageManager(const float carRadius);
    ~StageManager();
    CircuitTrack* GetCircuit()const;
    void Draw()const;
private:
    CircuitDataLoader circuitDataLoader;
    CircuitTrack* circuit;
    SkyDome* skyDome;
};