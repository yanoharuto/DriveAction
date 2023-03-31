#pragma once
#include <string>
#include <map>
#include "ModelUpdater.h"
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
    /// <param name="assetPass"></param>
    /// <returns></returns>
    static int GetDuplicate3DModelAssetHandle(std::string assetPass);
private :
    static const std::string genericPass;
    //model�̃A�h���X��Ⴄ�ƃ��f���n���h����Ԃ�
    static std::map<std::string, int> assetMap;
};

