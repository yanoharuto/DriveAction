#pragma once
#include "Object.h"
/// <summary>
/// スカイドーム
/// </summary>
class SkyDome final :public Object
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

