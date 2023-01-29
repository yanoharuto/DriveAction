#pragma once
#include "SoundPlayer.h"
#include "PlaySceeneProgressEnum.h"
#include "RacerManager.h"
#include "Timer.h"
#include "PlaySceneCamera.h"
#include "CourceDataLoader.h"
#include "StageManager.h"
#include "CountDown.h"
#include "MiniMap.h"
#include "PostGoalDirection.h"
#include "ScoreTime.h"
#include "GimmickObjManager.h"
#include "ConflictProcesser.h"
#include "PlayerRelatedUI.h"
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
    void MakeRankUI();
    RacerManager* racerManager;//�ԏ��̃}�l�[�W���[
    StageManager* stageManager;//�X�e�[�W�̃}�l�[�W���[
    Timer* timer;//���Ԍo�ߊϑ�
    PlaySceneCamera* camera;//�J����
    CourceDataLoader* courceDataLoader;
    CountDown* countDown;
    MiniMap* miniMap;
    ScoreTime* scoreTime;
    PostGoalDirection* postGoalDirection;
    GimmickObjManager* gimmickObjManager;
    ConflictProcesser* conflictProcesser;
    PlayerRelatedUI* playerRelatedUI;
    SoundPlayer* soundPlayer;
    PlaySceeneProgress nowProgress;//�����̏������s�������߂�ϐ�
    int countUINum;
    const int minimapX=1080;
    const int minimapY=450;
    const int maxLap = 1;
    float gameStartTime = 0;
};