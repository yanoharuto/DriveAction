#pragma once
#include "PlaySceeneProgressEnum.h"
#include "UIManager.h"
#include "RacerManager.h"
#include "Timer.h"
#include "PlaySceneCamera.h"
#include "CourceDataLoader.h"
#include "StageManager.h"
#include "CountDown.h"
#include "MiniMap.h"
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
    void MakeCountDownUI();
    void MakeRankUI();
    UIManager* uiManager;//ui�ɂ��Ẵ}�l�[�W���[
    RacerManager* racerManager;//�ԏ��̃}�l�[�W���[
    StageManager* stageManager;//�X�e�[�W�̃}�l�[�W���[
    Timer* timer;//���Ԍo�ߊϑ�
    PlaySceneCamera* camera;//�J����
    CourceDataLoader* courceDataLoader;
    CountDown* countDown;
    MiniMap* miniMap;
    PlaySceeneProgress nowProgress;//�����̏������s�������߂�ϐ�
    UIData uiData;
    int countUINum;
    const int minimapX=1080;
    const int minimapY=450;
};