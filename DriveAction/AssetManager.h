#pragma once
#include <string>
#include <map>
#include "ModelUpdater.h"
/// <summary>
/// アセットの複製とかする用
/// </summary>
class AssetManager
{
public:
    AssetManager();
    ~AssetManager();
    /// <summary>
    /// modelをロードして複製できるようにする
    /// </summary>
    /// <param name="assetPass"></param>
    /// <returns></returns>
    static int GetDuplicate3DModelAssetHandle(std::string assetPass);
private :
    static const std::string genericPass;
    //modelのアドレスを貰うとモデルハンドルを返す
    static std::map<std::string, int> assetMap;
};

