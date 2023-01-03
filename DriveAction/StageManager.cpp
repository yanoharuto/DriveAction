#include "StageManager.h"
#include "Utility.h"


StageManager::StageManager(const float carRadius)
{
    circuit = new CircuitTrack(carRadius);
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
