#pragma once
#include "StringUI.h"
#include "ImgUI.h"
#include "SwitchUI.h"
#include "SceneFlowBase.h"
#include <string>
/// <summary>
/// リザルトシーンの処理の流れ
/// </summary>
class ResultSceneFlow:public SceneFlowBase
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    ResultSceneFlow();

    ~ResultSceneFlow();
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name="deltaTime"></param>
    void Update()override;
    /// <summary>
    /// 描画
    /// </summary>
    void Draw()override;
private:
    //背景のアドレス
    const std::string resultBackImgPass = "data/result/resultGraph.png";
    
    //スコアのUI
    StringUI* rankUI;
    //スペースキーの催促
    SwitchUI* switchUI;
    ImgUI* backGround;
};

