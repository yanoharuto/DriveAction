#include "AssetManager.h"
#include "DxLib.h"
#include "Utility.h"
const std::string AssetManager::genericPass = "data/model/";
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
/// <param name="assetPass"></param>
/// <returns></returns>
int AssetManager::GetDuplicate3DModelAssetHandle(std::string assetPass)
{
    if (!assetMap.contains(assetPass))//まだロードしてないならロードする
    {
        std::string str = genericPass + assetPass;
        assetMap.insert(std::make_pair(assetPass, MV1LoadModel(str.c_str())));
    }
    return assetMap[assetPass];
}