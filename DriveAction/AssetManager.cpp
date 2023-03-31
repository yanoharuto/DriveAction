#include "AssetManager.h"
#include "DxLib.h"
#include "Utility.h"
const std::string AssetManager::genericPass = "data/model/";
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
/// <param name="assetPass"></param>
/// <returns></returns>
int AssetManager::GetDuplicate3DModelAssetHandle(std::string assetPass)
{
    if (!assetMap.contains(assetPass))//�܂����[�h���ĂȂ��Ȃ烍�[�h����
    {
        std::string str = genericPass + assetPass;
        assetMap.insert(std::make_pair(assetPass, MV1LoadModel(str.c_str())));
    }
    return assetMap[assetPass];
}