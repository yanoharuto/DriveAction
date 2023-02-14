#pragma once
#include "StringUI.h"
#include "ImgUI.h"
#include "SwitchUI.h"
#include "SceneFlowBase.h"
#include <string>
/// <summary>
/// ���U���g�V�[���̏����̗���
/// </summary>
class ResultSceneFlow:public SceneFlowBase
{
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    ResultSceneFlow();

    ~ResultSceneFlow();
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name="deltaTime"></param>
    void Update(float deltaTime)override;
    /// <summary>
    /// �`��
    /// </summary>
    void Draw()override;
private:
    //�w�i�̃A�h���X
    const std::string resultBackImgAddress = "data/result/resultGraph.png";
    //�w�i�̃n���h��
    int backGraphHandle;
    //�X�R�A��UI
    StringUI* scoreUI;
    StringUI* rankUI;
    //�X�y�[�X�L�[�̍Ñ�
    SwitchUI* switchUI;
};

