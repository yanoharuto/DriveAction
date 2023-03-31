#include "StageManager.h"
#include "Utility.h"
#include "CourceDataLoader.h"
StageManager::StageManager()
{
    circuit = new CircuitTrack();
    skyDome = new SkyDome();
}


StageManager::~StageManager()
{
    SAFE_DELETE(circuit);
    SAFE_DELETE(skyDome);
}

void StageManager::Update()
{
    skyDome->Update();
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
