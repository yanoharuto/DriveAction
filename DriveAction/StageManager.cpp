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
    circuit = new CircuitTrack(courceDataLoader->GetCourceAddress(),courceDataLoader->GetOutsideAddress());
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

std::string StageManager::GetCheckPoint() const
{
    return checkPointAddres;
}

void StageManager::Draw() const
{
    circuit->Draw();
    skyDome->Draw();
}
