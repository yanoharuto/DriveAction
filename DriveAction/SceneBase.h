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
    /// �f�X�g���N�^
    /// </summary>
    virtual ~SceneBase() 
    {
        SAFE_DELETE(timer);
        SAFE_DELETE(fadeInFadeOut);
        SAFE_DELETE(sceneFlow);
    }
    /// <summary>
    /// �V�[���̍X�V
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
            //�V�[�����Ƃ̏���
            sceneFlow->Update();
            if (sceneFlow->GetIsEndProccess())//�������I�������
            {
                fadeInFadeOut->FadeOutStart();
            }
            break;
        case FadeMode::fadeOutStart:
            fadeInFadeOut->FadeOut();
            break;
        case FadeMode::fadeOutEnd://�t�F�[�h�A�E�g���I������玟�̃V�[��
            return sceneFlow->GetNextSceneType();
            break;
        default:
            break;
        }
        timer->Update();
        return nowSceneType;
    };
    /// <summary>
    /// �`��
    /// </summary>
    void Draw()
    {
        sceneFlow->Draw();
        fadeInFadeOut->Draw();
    };
protected:
    //���̃V�[���̎��
    SceneType nowSceneType;
    //�t�F�[�h�C���t�F�[�h�A�E�g
    FadeInFadeOut* fadeInFadeOut;
    //�V�[���̏����̗���
    SceneFlowBase* sceneFlow;
    //�^�C�}�[
    Clock* timer;
};