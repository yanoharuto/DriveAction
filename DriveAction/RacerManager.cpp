#include "RacerManager.h"
#include "CPU.h"
#include "Player.h"
#include "CheckPoint.h"
#include "PlayerCar.h"
#include "Utility.h"
#include "RacerGenerater.h"
#include "CircuitTrack.h"
#include "CourceDataLoader.h"
#include "PlayerRelatedInfo.h"
/// <summary>
/// ������
/// </summary>
/// <param name="racerNum">�ԏ��̐��������X�g�ɒǉ������</param>
/// <returns></returns>
RacerManager::RacerManager(int cpuNum, CourceDataLoader* const courceDataLoader)
{
    racerNum = cpuNum > maxRacerNum ? maxRacerNum : cpuNum;
    playerInfoCenter = new PlayerInformationCenter();
    //����l�����𐶐�
    RacerGenerater* racerGenerater = new RacerGenerater();
    racerGenerater->CreateRacers(racerNum, &racerList, &player,playerInfoCenter);

    //�v���C���[�̏���������
    RacerRankInfo rankInfo{};

    for (auto i = racerList.begin(); i != racerList.end(); i++)
    {
        //�����N����ǉ�
        rankInfo.checkPointP = (*i)->GetCheckPointer();
        rankInfo.rankP = (*i)->GetRankPointer();
        racerRankList.push_front(rankInfo);
    }
    SAFE_DELETE(racerGenerater);
    
}
//�f�X�g���N�^
RacerManager::~RacerManager()
{
    for (auto ite = racerList.begin(); ite != racerList.end(); ite++)
    {
        SAFE_DELETE((*ite));
    }
    SAFE_DELETE(playerInfoCenter);
}
/// <summary>
/// �ԏ�肽���̍X�V
/// </summary>
/// <param name="deltaTime">�t���[���Ԃ̌o�ߎ���</param>
/// <param name="circuit">����R�[�X</param>
void RacerManager::RacerUpdate( )
{
    Racer* racer;
    ConflictExamineResultInfo conflictResultInfo;
    for (auto racerIte = racerList.begin(); racerIte != racerList.end(); racerIte++)
    {
        racer = *racerIte;
        //�Ԃ̍X�V�@
        racer->Update();
    }
    //�ʒu���Ƃ��X�V
    playerInfoCenter->UpdatePlayerRelatedInfo();
}
/// <summary>
/// �㉺�ɓ���
/// </summary>
void RacerManager::UpDown()
{
    Racer* racer;
    for (auto racerIte = racerList.begin(); racerIte != racerList.end(); racerIte++)
    {
        racer = *racerIte;
        racer->UpDown();
    }
}

/// <summary>
/// �v���C���[��UI�ɕK�v�ȏ���n��
/// </summary>
/// <returns></returns>
PlayerInformationCenter* RacerManager::GetPlayerRelatedInfo()
{
   return playerInfoCenter;
}


/// <summary>
  /// �`��
  /// </summary>
  /// <returns></returns>
void RacerManager::Draw()
{
    Racer* racer;
    for (auto racerIte = racerList.begin(); racerIte != racerList.end(); racerIte++)
    {
        racer = *racerIte;
        racer->Draw();
    }
}

ObjInfo RacerManager::GetPlayerCarPosDir() 
{
    return player->GetPlayerPosAndDir();
}