#pragma once
#include <string>
#include <map>
/// <summary>
/// �A�Z�b�g�̕����Ƃ�����p
/// </summary>
class AssetManager
{
public:
    AssetManager();
    ~AssetManager();
    /// <summary>
    /// model�����[�h���ĕ����ł���悤�ɂ���
    /// </summary>
    /// <param name="assetAddress"></param>
    /// <returns></returns>
    static int Get3DModelAssetHandle(std::string assetAddress);
private :
};
