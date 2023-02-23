#pragma once
#include <string>
#include <map>
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
    /// <param name="assetAddress"></param>
    /// <returns></returns>
    static int GetDuplicate3DModelAssetHandle(std::string assetAddress);
private :
};

