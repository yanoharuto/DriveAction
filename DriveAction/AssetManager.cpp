#include "AssetManager.h"
#include "DxLib.h"
#include "Utility.h"
const std::string AssetManager::genericAddress = "data/model/";
//modelのアドレスを貰うとモデルハンドルを返す
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
/// 複製したモデルを渡す
/// </summary>
/// <param name="assetAddress"></param>
/// <returns></returns>
int AssetManager::GetDuplicate3DModelAssetHandle(std::string assetAddress)
{
    if (!assetMap.contains(assetAddress))//まだロードしてないならロードする
    {
        std::string str = genericAddress + assetAddress;
        assetMap.insert(std::make_pair(assetAddress, MV1LoadModel(str.c_str())));
    }
    return assetMap[assetAddress];
}