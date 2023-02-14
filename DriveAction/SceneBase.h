#pragma once
#include "FadeInFadeOut.h"
#include "Timer.h"
#include "Utility.h"
#include "SceneFlowBase.h"
enum class SceneType
{
    TITLE,
    PLAY,
    RESULT
};

class SceneBase abstract
{
public:
    SceneBase(SceneType _SceneType)
    {
        nowSceneType = _SceneType;
        fadeInFadeOut = new FadeInFadeOut();
        timer = new Timer();
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
    SceneType Update()
    {
        timer->Update();
        switch (fadeInFadeOut->GetFadeMode())
        {
        case FadeMode::fadeInStart:

            fadeInFadeOut->FadeIn(timer->GetDeltaTime());
            break;
        case FadeMode::fadeInEnd:
            //シーンごとの処理
            sceneFlow->Update(timer->GetDeltaTime());
            if (sceneFlow->GetIsEndProccess())//処理が終わったら
            {
                fadeInFadeOut->FadeOutStart();
            }
            break;
        case FadeMode::fadeOutStart:
            fadeInFadeOut->FadeOut(timer->GetDeltaTime());
            break;
        case FadeMode::fadeOutEnd://フェードアウトが終わったら次のシーン
            return nextSceneType;
            break;
        default:
            break;
        }
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
    //次のシーンの種類
    SceneType nextSceneType;
    //フェードインフェードアウト
    FadeInFadeOut* fadeInFadeOut;
    //シーンの処理の流れ
    SceneFlowBase* sceneFlow;
    //タイマー
    Timer* timer;
};