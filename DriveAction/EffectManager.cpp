#include <unordered_map>
#include "EffectManager.h"
#include "EffekseerForDXLib.h"
#include "CSVFileLoader.h"
#include "Utility.h"
std::unordered_map <EffectKind, int> EffectManager:: effectMap;
std::vector<std::string> EffectManager::initDataVec;
EffectManager::EffectManager()
{
    CSVFileLoader* initDataFile = new CSVFileLoader(initDataPassFile);
    initDataVec = initDataFile->GetLoadData();
    SAFE_DELETE(initDataFile);
}

EffectManager::~EffectManager()
{
    for (auto ite = effectMap.begin(); ite != effectMap.end(); ite++)
    {
        DeleteEffekseerEffect((*ite).second);
    }
    effectMap.clear();
}

void EffectManager::LoadEffectManager(EffectKind kind)
{
    if (!effectMap.contains(kind))
    {
        //ÉfÅ[É^ì«Ç›éÊÇË
        CSVFileLoader* initDataFile = new CSVFileLoader(initDataVec[kind]);

        std::vector<std::string> dataVec = initDataFile->GetLoadData();

        const char* effectPass = dataVec[EffectInitData::effectPass].c_str();

        float size = atof(dataVec[EffectInitData::effectSize].c_str());

        int effectHandle = LoadEffekseerEffect(effectPass, size);
        effectMap.insert(std::make_pair(kind, effectHandle));
    }
}

int EffectManager::GetPlayEffect3D(EffectKind kind)
{
    int isPlay = -1;
    if (effectMap.contains(kind))
    {
        isPlay = PlayEffekseer3DEffect(effectMap[kind]);
    }
    return isPlay;
}

int EffectManager::GetPlayEffect2D(EffectKind kind)
{
    return PlayEffekseer3DEffect(effectMap[kind]);
}

bool EffectManager::IsPlayEffect(EffectKind kind)
{
    return IsEffekseer3DEffectPlaying(effectMap[kind]);
}