#include "AssetManager.h"
#include "DxLib.h"
#include "Utility.h"
const std::string AssetManager::genericAddress = "data/model/";
//model�̃A�h���X��Ⴄ�ƃ��f���n���h����Ԃ�
std::map<std::string, int> AssetManager::assetMap;
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
/// <summary>
/// �����������f����n��
/// </summary>
/// <param name="assetAddress"></param>
/// <returns></returns>
int AssetManager::GetDuplicate3DModelAssetHandle(std::string assetAddress)
{
    if (!assetMap.contains(assetAddress))//�܂����[�h���ĂȂ��Ȃ烍�[�h����
    {
        std::string str = genericAddress + assetAddress;
        assetMap.insert(std::make_pair(assetAddress, MV1LoadModel(str.c_str())));
    }
    return assetMap[assetAddress];
}