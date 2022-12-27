#pragma once
#include "Stage.h"
/// <summary>
/// スカイドーム
/// </summary>
class SkyDome final :public Stage
{
public:
    /// <summary>
    /// modelのロードとタグ付け
    /// </summary>
    /// <returns></returns>
    SkyDome();
    //modelのデリート
    ~SkyDome();
    /// <summary>
    /// modelの描画
    /// </summary>
    void Draw();

private:
    int modelHandle;
};

