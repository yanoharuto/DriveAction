#include "StageManager.h"
#include "Utility.h"
#include "StageSelect.h"
#include "DataAddresLoader.h"
#include "StageDataClassificationStruct.h"
StageManager::StageManager()
{
    std::list<std::string> stageDataList;
    StageDataAddress address;
    DataAddressLoader circuitDataLoader;
    circuitDataLoader.GetString(&stageDataList, StageSelect::GetLoadeStageName()+address.cStageAddress);
    std::string courceAdress = *stageDataList.begin();//サーキットの走る部分
    std::string outsideAdress = *++stageDataList.begin();//サーキットの外
    checkPointAddres = StageSelect::GetLoadeStageName() + address.cGoalStatus;
    circuit = new CircuitTrack(courceAdress.c_str(), outsideAdress.c_str());
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
