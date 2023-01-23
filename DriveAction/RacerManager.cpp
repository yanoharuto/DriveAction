#include "RacerManager.h"
#include "CPUCar.h"
#include "CheckPoint.h"
#include "Player.h"
#include "Utility.h"
#include "CircuitTrack.h"
#include "StageDataAddressStruct.h"
#include "CourceDataLoader.h"
#include <algorithm>
/// <summary>
/// ������
/// </summary>
/// <param name="racerNum">�ԏ��̐��������X�g�ɒǉ������</param>
/// <returns></returns>
RacerManager::RacerManager(int cpuNum, CourceDataLoader* const courceDataLoader)
{
    racerNum = cpuNum > maxRacerNum ? maxRacerNum : cpuNum;
    //�R�[�X�̏��Ƃ�������������炤
    CircuitData circuitData{ courceDataLoader->GetCheckPointPosList(),courceDataLoader->GetCheckPointDirList() };
    std::list<VECTOR> firstPosList = courceDataLoader->GetCarFirstPosList();
    //�ŏ��̈�s�͌��������Ȃ̂ŏ���
    firstPosList.erase(firstPosList.begin());
    //�|�W�V�����̃C�e���[�^�[
    std::list<VECTOR>::iterator firstPosIte = firstPosList.begin();
    //�v���C���[�̏���������
    RacerRankInfo rankInfo{};
    player = {};
    for (int i = 0; i < racerNum; i++)
    {
        firstPosIte++;
        if (i == 0)
        {
            racerInstanceArray[i].car = new Player(*firstPosIte, courceDataLoader->GetCarFirstDir());
            racerInstanceArray[i].rank = 0;
            racerInstanceArray[i].checkPoint = new CheckPoint(circuitData);
            player.car = racerInstanceArray[i].car;
            player.rank = &racerInstanceArray[i].rank;
            player.checkPoint = racerInstanceArray[i].checkPoint;
        }
        else
        {
            racerInstanceArray[i].car = new CPUCar(*firstPosIte, courceDataLoader->GetCarFirstDir());
            racerInstanceArray[i].rank = 0;
            racerInstanceArray[i].checkPoint = new CheckPoint(circuitData);
        }
        racerList.push_front(&racerInstanceArray[i]);
        rankInfo.checkPointP = racerInstanceArray[i].checkPoint;
        rankInfo.rankP = &racerInstanceArray[i].rank;
        racerRankList.push_front(rankInfo);
    }
    UIData uiData;
    uiData.x = SCREEN_WIDTH / 13;
    uiData.y = SCREEN_HEIGHT / 9;
    uiData.dataHandle = CreateFontToHandle("BIZ UD�S�V�b�N", 64, 3, DX_FONTTYPE_NORMAL);
    rankUI = new StringUI(GetColor(0,255,0), uiData);

    uiData.x = SCREEN_WIDTH / 15;
    uiData.y = SCREEN_HEIGHT / 13;
    uiData.dataHandle = CreateFontToHandle("BIZ UD�S�V�b�N", 64, 3, DX_FONTTYPE_NORMAL);
    rapUI = new StringUI(GetColor(0, 0, 0), uiData);
}
//�f�X�g���N�^
RacerManager::~RacerManager()
{
    for (int i = 0; i < static_cast<signed>(racerList.size()); i++)
    {
        SAFE_DELETE(racerInstanceArray[i].car);
        SAFE_DELETE(racerInstanceArray[i].checkPoint);
    }
    SAFE_DELETE(rankUI);
}
/// <summary>
/// �ԏ�肽���̍X�V
/// </summary>
/// <param name="deltaTime">�t���[���Ԃ̌o�ߎ���</param>
/// <param name="circuit">����R�[�X</param>
void RacerManager::RacerUpdate(const float deltaTime, CircuitTrack* circuit)
{
    std::list<Racer*>::iterator racerIte;
    Racer* racer;
    bool hitFlag;
    NeighborhoodInfo neighInfo;
    ConflictExamineResultInfo conflictInfo;
    for (racerIte = racerList.begin(); racerIte != racerList.end(); racerIte++)
    {
        racer = *racerIte;
        conflictInfo.SetObjInfo(false,racer->car);
        //����ɉ������邩���ׂ�
        hitFlag = circuit->GetOutsideHitFlag(conflictInfo);
        neighInfo = circuit->GetOutsideExamineInfo(racer->car->GetNeighExamineInfo());
        //�Ԃ̍X�V�@
        racer->car->Update(deltaTime, hitFlag,neighInfo);
        //�`�F�b�N�|�C���g�̍X�V�̍X�V
        conflictInfo.SetObjInfo(true, racer->car);
        //�Ԃ��`�F�b�N�|�C���g��ʉ߂��������ׂ�
        racer->checkPoint->CheckPointUpdate(conflictInfo);
        //�ԂɎ��̖ړI�n��`����
        conflictInfo.SetObjInfo(true, racer->checkPoint);
        racer->car->ConflictProcess(deltaTime, conflictInfo);
        //�R�[�X�̕��Ƃ��ɂԂ����������ׂ�
        conflictInfo.SetObjInfo(false, racer->car);
        conflictInfo = circuit->GetCourceConflictInfo(conflictInfo);
        if (conflictInfo.hitFlag)            //�Ԃ����Ă���Փˏ���
        {
            racer->car->ConflictProcess(deltaTime, conflictInfo);
        }
    }
}
/// <summary>
/// �����̕��̂ɂԂ����������ׂ�
/// </summary>
/// <param name="obj">���ׂ�������</param>
void RacerManager::ArgumentConflictProcess(float deltaTime,Object* obj)
{
    ConflictExamineResultInfo conflictInfo;
    conflictInfo.SetObjInfo(false,obj);
    std::list<Racer*>::iterator racerIte;
    Racer* racer;
    for (racerIte = racerList.begin(); racerIte != racerList.end(); racerIte++)
    {
        racer = *racerIte;
        //car���g�Ɠ����蔻�����Ă���ʂ�Ȃ�
        if (racer->car != obj)
        {
            //�������Ă邩���ׂ�@
            if (hitChecker.HitCheck(racer->car, obj))
            {
                racer->car->ConflictProcess(deltaTime,conflictInfo);
            }
        }
    }
}
void RacerManager::RacerRankUpdate()
{
    std::list<RacerRankInfo>::iterator rankIte;
    RacerRankInfo* swapRankInfo = nullptr;
    int transitCheckCount = 0;//�`�F�b�N�|�C���g�ʉ߉�
    int maxTransitCheckCount = 0;//�`�F�b�N�|�C���g�ő�ʉ߉�
    float checkPointBetween = 0;//���̃`�F�b�N�|�C���g�܂ł̋�������
    float minCheckPointBetween = 0;//���̃`�F�b�N�|�C���g�܂ł̌���̍ŒZ����
    //�\�[�g
    for (rankIte = racerRankList.begin(); rankIte != racerRankList.end(); rankIte++)
    {   
        minCheckPointBetween = (*rankIte).checkPointP->GetCheckPointDistance();
        maxTransitCheckCount= (*rankIte).checkPointP->GetTransitCheckPointCount();
        swapRankInfo = nullptr;
        for (std::list<RacerRankInfo>::iterator rankIte2 = rankIte; rankIte2 != racerRankList.end(); rankIte2++)
        {
            transitCheckCount = (*rankIte2).checkPointP->GetTransitCheckPointCount();
            checkPointBetween = (*rankIte2).checkPointP->GetCheckPointDistance();
            //�`�F�b�N�|�C���g�����߂���
            if (checkPointBetween < minCheckPointBetween)
            {
                //�`�F�b�N�|�C���g��ʉ߂����񐔂������l����荂����
                if (transitCheckCount >= maxTransitCheckCount)
                {
                    minCheckPointBetween = checkPointBetween;
                    maxTransitCheckCount = transitCheckCount;
                    swapRankInfo = &(*rankIte2);
                }
            }
        }
        //�X���b�v
        if (swapRankInfo != nullptr)
        {
            std::swap((*rankIte), *swapRankInfo);
        }
    }
    //���ʍX�V
    int rank = 0;
    for (rankIte = racerRankList.begin(); rankIte != racerRankList.end(); rankIte++)
    {
        *(*rankIte).rankP = ++rank;
    }
    rankUI->UpdateString(std::to_string(*player.rank));
    rapUI->UpdateString(std::to_string(player.checkPoint->GetGoalCount()));
}
/// <summary>
/// �ԏ�肽�����m�łԂ����ĂȂ������ׂ�
/// </summary>
void RacerManager::RacerConflictProcces(float deltaTime)
{
    std::list<Racer*>::iterator racerIte;
    Racer* racer;
    for (racerIte = racerList.begin(); racerIte != racerList.end(); racerIte++)
    {
        racer = *racerIte;
        ArgumentConflictProcess(deltaTime,racer->car);
    }
}
/// <summary>
/// �v���C���[�̃S�[�������񐔂�Ԃ�
/// </summary>
/// <returns></returns>
int RacerManager::GetPlayerGoalCount()
{
    return player.checkPoint->GetGoalCount();
}

int RacerManager::GetPlayerRank()
{
    return *player.rank;
}

/// <summary>
  /// �`��
  /// </summary>
  /// <returns></returns>
void RacerManager::Draw()
{
    std::list<Racer*>::iterator racerIte;
    Racer* racer;
    for (racerIte = racerList.begin(); racerIte != racerList.end(); racerIte++)
    {
        racer = *racerIte;
        racer->car->Draw();
    }
    rankUI->DrawUI();
    //rapUI->DrawUI();
}
/// <summary>
/// ��ԍŏ��ɒǉ������I�u�W�F�N�g��Ԃ�
/// </summary>
/// <returns></returns>
Object* RacerManager::GetPlayerCar() const
{
    Car* playerCar= player.car;
    return playerCar;
}

