#pragma once
#include <string>
#include<list>
#include "VECTOR3Loader.h"
#include "DxLib.h"
/// <summary>
/// コース情報の保管庫
/// </summary>
class CourceDataLoader
{
public:
    /// <summary>
    /// コース情報
    /// </summary>
    CourceDataLoader();
    //デストラクタ
    ~CourceDataLoader();
    /// <summary>
    /// コースのミニマップ
    /// </summary>
    /// <returns></returns>
    static const std::string GetStageDataGenericPass();
    static std::list<VECTOR> GetVECTORData(std::string Pass);
private:
    //データの置き場所
    const std::string prevPass = "data/stageData/";
    //共通のアドレス
    static std::string genericPass;
};