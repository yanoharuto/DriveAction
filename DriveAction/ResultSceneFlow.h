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
    void Update()override;
    /// <summary>
    /// �`��
    /// </summary>
    void Draw()override;
private:
    //�w�i�̃A�h���X
    const std::string resultBackImgPass = "data/result/resultGraph.png";
    
    //�X�R�A��UI
    StringUI* rankUI;
    //�X�y�[�X�L�[�̍Ñ�
    SwitchUI* switchUI;
    ImgUI* backGround;
};

