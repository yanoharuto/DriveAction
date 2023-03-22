#include "StageManager.h"
#include "Utility.h"
#include "CourceDataLoader.h"
StageManager::StageManager()
{
    circuit = new CircuitTrack();
    skyDome = new SkyDome();
}

StageManager::StageManager(CourceDataLoader* courceDataLoader)
{
    circuit = new CircuitTrack();
    skyDome = new SkyDome();
}

StageManager::~StageManager()
{
    SAFE_DELETE(circuit);
    SAFE_DELETE(skyDome);
}

CircuitTrack* StageManager::GetCircuit() const
{
    return circuit;
}


void StageManager::Draw() const
{
    circuit->Draw();
    skyDome->Draw();
}
