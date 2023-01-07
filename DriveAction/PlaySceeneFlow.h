#pragma once
#include "PlaySceeneProgressEnum.h"
#include "UIManager.h"
#include "LacerManager.h"
#include "Timer.h"
#include "PlaySceneCamera.h"
#include "StageManager.h"
/// <summary>
/// �ǂ��������Ԃŏ������s�������߂�
/// </summary>
class PlaySceeneFlow
{
public:
    /// <summary>
    /// ������
    /// </summary>
    /// <returns></returns>
    PlaySceeneFlow();
    ~PlaySceeneFlow();
    /// <summary>
    /// �v���C�V�[���̍X�V
    /// </summary>
    /// <returns></returns>
    PlaySceeneProgress Update();
    /// <summary>
    /// �`��
    /// </summary>
    void Draw();
private:
    UIManager* uiManager;//ui�ɂ��Ẵ}�l�[�W���[
    LacerManager* lacerManager;//�ԏ��̃}�l�[�W���[
    StageManager* stageManager;//�X�e�[�W�̃}�l�[�W���[
    Timer* timer;//���Ԍo�ߊϑ�
    PlaySceneCamera* camera;//�J����
    PlaySceeneProgress nowProgress;//�����̏������s�������߂�ϐ�
};