#pragma once
#include "CourceDataLoader.h"
#include "Saw.h"
#include "AccelerationFloor.h"
#include "ConflictExamineResultInfo.h"
/// <summary>
/// �������Ƃ���Q���̃}�l�[�W���[
/// </summary>
class GimmickObjManager
{
public:
    GimmickObjManager();
    GimmickObjManager(CourceDataLoader* courceDataLoader);
    ~GimmickObjManager();
    void Draw();
    /// <summary>
    /// �����̃I�u�W�F�N�g�ƂԂ������M�~�b�N�̏���Ԃ�
    /// </summary>
    /// <param name="argumentObjInfo"></param>
    /// <returns></returns>
    ConflictExamineResultInfo GetArgumentAndConflictGimmickInfo(ConflictExamineResultInfo argumentObjInfo);
private:
    std::list<Saw*> sawList;
    std::list<AccelerationFloor*> accelerationFloorList;
    int modelResource;
};

