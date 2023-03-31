#pragma once
#include "FadeInFadeOut.h"
#include "Clock.h"
#include "Utility.h"
#include "SceneFlowBase.h"
#include "SceneType.h"

class SceneBase abstract
{
public:
    SceneBase(SceneType _SceneType)
    {
        nowSceneType = _SceneType;
        fadeInFadeOut = new FadeInFadeOut();
        timer = new Clock();
    }
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~SceneBase() 
    {
        SAFE_DELETE(timer);
        SAFE_DELETE(fadeInFadeOut);
        SAFE_DELETE(sceneFlow);
    }
    /// <summary>
    /// シーンの更新
    /// </summary>
    /// <returns></returns>
    virtual SceneType Update()
    {
        switch (fadeInFadeOut->GetFadeMode())
        {
        case FadeMode::fadeInStart:

            fadeInFadeOut->FadeIn();
            break;
        case FadeMode::fadeInEnd:
            //シーンごとの処理
            sceneFlow->Update();
            if (sceneFlow->GetIsEndProccess())//処理が終わったら
            {
                fadeInFadeOut->FadeOutStart();
            }
            break;
        case FadeMode::fadeOutStart:
            fadeInFadeOut->FadeOut();
            break;
        case FadeMode::fadeOutEnd://フェードアウトが終わったら次のシーン
            return sceneFlow->GetNextSceneType();
            break;
        default:
            break;
        }
        timer->Update();
        return nowSceneType;
    };
    /// <summary>
    /// 描画
    /// </summary>
    void Draw()
    {
        sceneFlow->Draw();
        fadeInFadeOut->Draw();
    };
protected:
    //このシーンの種類
    SceneType nowSceneType;
    //フェードインフェードアウト
    FadeInFadeOut* fadeInFadeOut;
    //シーンの処理の流れ
    SceneFlowBase* sceneFlow;
    //タイマー
    Clock* timer;
};