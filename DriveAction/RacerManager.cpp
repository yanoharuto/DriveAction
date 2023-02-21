#include "RacerManager.h"
#include "CPU.h"
#include "Player.h"
#include "CheckPoint.h"
#include "PlayerCar.h"
#include "Utility.h"
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
    std::list<VECTOR> firstPosList = courceDataLoader->GetCarFirstPosList();
    //�ŏ��̈�s�͌��������Ȃ̂ŏ���
    firstPosList.erase(firstPosList.begin());
    //�|�W�V�����̃C�e���[�^�[
    auto firstPosIte = firstPosList.begin();
    //�v���C���[�̏���������
    RacerRankInfo rankInfo{};
    Racer* newRacer;
    //�R�[�X�̏��Ƃ�������������炤
    VECTOR firstDir = courceDataLoader->GetCarFirstDir();
    CircuitData circuitData{ courceDataLoader->GetCheckPointPosList(),courceDataLoader->GetCheckPointDirList() };
    //���[�T�[�̐�����New����
    for (int i = 0; i < racerNum + 1; i++)
    {
        firstPosIte++;
        if (i == 0)
        {
            player = new Player(circuitData, *firstPosIte, firstDir);
            newRacer = player;
        }
        else
        {
            newRacer = new CPU(circuitData, *firstPosIte, firstDir);
        }
        racerList.push_front(newRacer);
        //�����N����ǉ�
        rankInfo.checkPointP = newRacer->GetCheckPointer();
        rankInfo.rankP = newRacer->GetRankPointer();
        racerRankList.push_front(rankInfo);
    }
}
//�f�X�g���N�^
RacerManager::~RacerManager()
{
    for (auto ite = racerList.begin(); ite != racerList.end(); ite++)
    {
        SAFE_DELETE((*ite));
    }
}
/// <summary>
/// �ԏ�肽���̍X�V
/// </summary>
/// <param name="deltaTime">�t���[���Ԃ̌o�ߎ���</param>
/// <param name="circuit">����R�[�X</param>
void RacerManager::RacerUpdate(const float deltaTime, CircuitTrack* circuit, DamageObjectGenerator* damageObj)
{
    Racer* racer;
    bool hitFlag;
    ConflictExamineResultInfo conflictResultInfo;
    for (auto racerIte = racerList.begin(); racerIte != racerList.end(); racerIte++)
    {
        racer = *racerIte;
        //����ɉ������邩���ׂ�
        hitFlag = circuit->GetOutsideHitFlag(racer->GetCarHitCheckExamineInfo());
        //�Ԃ̍X�V�@
        racer->Update(deltaTime, hitFlag, damageObj);
    }
}
/// <summary>
/// �����̕��̂ɂԂ����������ׂ�
/// </summary>
/// <param name="obj">���ׂ�������</param>
void RacerManager::ArgumentConflictProcess(float deltaTime,Racer* obj)
{
    Racer* racer;
    for (auto racerIte = racerList.begin(); racerIte != racerList.end(); racerIte++)
    {
        racer = *racerIte;
        //car���g�Ɠ����蔻�����Ă���ʂ�Ȃ�
        if (racer!= obj)
        {
            //�������Ă邩���ׂ�@
            if (racer->HitCheck(obj->GetCarHitCheckExamineInfo()))
            {
                //�Ԃ���������ɂ�����n��
                ConflictExamineResultInfo resultInfo = obj->GetConflictExamineResultInfo();
                resultInfo.hitFlag = true;
                racer->ConflictProcces(resultInfo, deltaTime);
                resultInfo = racer->GetConflictExamineResultInfo();
                resultInfo.hitFlag = false;
                obj->ConflictProcces(resultInfo,deltaTime);
            }
        }
    }
}
void RacerManager::RacerRankUpdate()
{
    int transitCheckCount = 0;//�`�F�b�N�|�C���g�ʉ߉�
    int maxTransitCheckCount = 0;//�`�F�b�N�|�C���g�ő�ʉ߉�
    float checkPointBetween = 0;//���̃`�F�b�N�|�C���g�܂ł̋�������
    float minCheckPointBetween = 0;//���̃`�F�b�N�|�C���g�܂ł̌���̍ŒZ����
    int rank = 0;
    //�\�[�g
    for (auto rankIte = racerRankList.begin(); rankIte != racerRankList.end(); rankIte++)
    {   
        minCheckPointBetween = (*rankIte).checkPointP->GetCheckPointDistance();//�`�F�b�N�|�C���g�܂ł̍����o��
        maxTransitCheckCount = (*rankIte).checkPointP->GetTransitCheckPointCount();//�ʉ߉񐔂��o��
        RacerRankInfo* swapRankInfo = nullptr;//����̕ϐ����X�V���ꂽ�璆�g���X�V
        for (auto rankIte2 = rankIte; rankIte2 != racerRankList.end(); rankIte2++)
        {
            transitCheckCount = (*rankIte2).checkPointP->GetTransitCheckPointCount();
            checkPointBetween = (*rankIte2).checkPointP->GetCheckPointDistance();
            //�`�F�b�N�|�C���g�ɂ��߂���
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
        //���ʍX�V
        *(*rankIte).rankP = ++rank;
    }
}
/// <summary>
/// ���[�T�[�̓����蔻�菈��
/// </summary>
void RacerManager::RacerConflictProcces(ConflictProcesser* conflictProcesser,CircuitTrack* circuit,float deltaTime)
{
    Racer* racer;
    ConflictExamineResultInfo conflictResultInfo;
    for (auto racerIte = racerList.begin(); racerIte != racerList.end(); racerIte++)
    {
        racer = *racerIte;
        //�ԓ��m�łԂ����ĂȂ������ׂ�
        ArgumentConflictProcess(deltaTime, racer);

        //�������Ƃ��ɂԂ����Ă���
        conflictResultInfo = conflictProcesser->GetConflictObjInfo(racer->GetCarHitCheckExamineInfo());
        if (conflictResultInfo.hitFlag)
        {
            racer->ConflictProcces(conflictResultInfo, deltaTime);
        }
        //�R�[�X�̕��ɂԂ����������ׂ�
        conflictResultInfo = circuit->GetCourceConflictInfo(racer->GetCarHitCheckExamineInfo());
        if (conflictResultInfo.hitFlag)            //�Ԃ����Ă���Փˏ���
        {
            racer->ConflictProcces(conflictResultInfo,deltaTime);
        }

    }
}



/// <summary>
/// �v���C���[��UI�ɕK�v�ȏ���n��
/// </summary>
/// <returns></returns>
PlayerRelatedInfo RacerManager::GetPlayerRelatedInfo()
{
   return player->GetRelatedInfo();
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

PlaySceneCameraArgumentInfo RacerManager::GetPlayerCarPosDir() 
{
    return player->GetCameraArgumentInfo();
}

