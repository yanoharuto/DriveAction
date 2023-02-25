#include "Racer.h"
#include "Car.h"
#include "CheckPoint.h"
#include "HitChecker.h"
#include"Utility.h"
#include "OriginalMath.h"
static const float courceOutMaxCount = 5.8f;
Racer::Racer()
{
    checkPoint = new CheckPoint();
    itemHolder = new ItemHolder();
    rank = 0;
}

Racer::~Racer()
{
    SAFE_DELETE(checkPoint);
    SAFE_DELETE(itemHolder);
    SAFE_DELETE(car);
}

void Racer::Update(float deltaTime, bool outsideHitFlag,DamageObjectGenerator* damageObjGene)
{
    //�v���C���[�Ƌ��ʂ̏���
    CommonUpdate(deltaTime,outsideHitFlag,damageObjGene);
    ItemInfo itemInfo = itemHolder->GetItemInfo();
    //�A�C�e�����g����Ƃ��͎g��
    if (itemInfo.itemSituation != ItemUseSituation::DoneUsing && itemInfo.itemTag != non)
    {
        itemHolder->UseItem(car->GetItemArgumentInfo());
    }

}

bool Racer::HitCheck(HitCheckExamineObjectInfo objInfo)
{
    HitChecker hitChecker;
    //�������Ă邩���ׂ�@
    if (hitChecker.HitCheck(car, objInfo))
    {
        return true;
    }
    return false;
}

void Racer::Draw()
{
    car->Draw();
    itemHolder->ItemDraw();
}

void Racer::ConflictProcces(ConflictExamineResultInfo conflictResultInfo, float deltaTime)
{
    if (conflictResultInfo.tag == ObjectTag::itemBox)
    {
        itemHolder->SelectItem(rank);
    }
    else
    {
        car->ConflictProccess(deltaTime, conflictResultInfo);
    }
}

void Racer::CommonUpdate(float deltaTime, bool outsideHitFlag, DamageObjectGenerator* damageObjGene)
{
    //�A�C�e���̍X�V
    itemHolder->Update(damageObjGene, car->GetItemArgumentInfo(), deltaTime);
    //�Ԃ̓����蔻����
    HitCheckExamineObjectInfo racerHitCheckExamineInfo;
    racerHitCheckExamineInfo.SetExamineInfo(*car);
    //�Ԃ��`�F�b�N�|�C���g��ʉ߂��������ׂ�
    ConflictExamineResultInfo conflictResultInfo = checkPoint->CheckPointUpdate(racerHitCheckExamineInfo);
    if (conflictResultInfo.hitFlag)
    {
        //�ԂɎ��̖ړI�n��`����
        car->ConflictProccess(deltaTime, conflictResultInfo);
    }
    //�R�[�X�O�ɏo����
    if (outsideHitFlag)
    {
        //�R�[�X�O�ɏo�����Ԃ�ǉ�
        //courceOutCount += deltaTime;
        if (courceOutCount > courceOutMaxCount)
        {
            car->SetCourceOutProccess(checkPoint->GetLastPos(),checkPoint->GetLastDir());
            courceOutCount = 0.0f;
        }
    }
    else if (VDot(car->GetDir(), checkPoint->GetDir()) <= -0.5f)
    {
        //�R�[�X�O�ɏo�����Ԃ�ǉ�
        //courceOutCount += deltaTime;
        if (courceOutCount > courceOutMaxCount)
        {
            car->SetCourceOutProccess(checkPoint->GetLastPos(), checkPoint->GetLastDir());
            courceOutCount = 0.0f;
        }
        reverse = true;
    }
    else
    {
        reverse = false;
        //�R�[�X����o�Ă��Ȃ�������R�[�X�A�E�g���Ԃ����炷
        courceOutCount = courceOutCount > 0.001f ? courceOutCount - deltaTime : 0.0f;
    }
}

void Racer::SetCarPointer(Car* newCar)
{
    car = newCar;
}

HitCheckExamineObjectInfo Racer::GetCarHitCheckExamineInfo()
{
    HitCheckExamineObjectInfo objInfo;
    objInfo.SetExamineInfo(*car);
    return objInfo;
}

ConflictExamineResultInfo Racer::GetConflictExamineResultInfo()
{
    ConflictExamineResultInfo info;
    info.SetObjInfo(false,car);
    return info;
}

int* Racer::GetRankPointer()
{
    return &rank;
}

CheckPoint* Racer::GetCheckPointer()
{
    return checkPoint;
}
