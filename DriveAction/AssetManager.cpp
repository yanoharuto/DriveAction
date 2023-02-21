#include "AssetManager.h"
#include "DxLib.h"
//model�̃A�h���X��Ⴄ�ƃ��f���n���h����Ԃ�
static std::map<std::string, int> assetMap;
AssetManager::AssetManager()
{
}

AssetManager::~AssetManager()
{
    for (auto ite = assetMap.begin(); ite != assetMap.end(); ite++)
    {
        MV1DeleteModel((*ite).second);
    }
    assetMap.clear();
}

int AssetManager::Get3DModelAssetHandle(std::string assetAddress)
{
    if (!assetMap.contains(assetAddress))//�܂����[�h���ĂȂ��Ȃ烍�[�h����
    {
        assetMap.insert(std::make_pair(assetAddress, MV1LoadModel(assetAddress.c_str())));
    }
    return MV1DuplicateModel(assetMap[assetAddress]);
}