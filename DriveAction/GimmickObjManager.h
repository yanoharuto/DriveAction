#pragma once
#include "CourceDataLoader.h"
#include "Actor.h"
#include "ConflictProcesser.h"
/// <summary>
/// �������Ƃ���Q���̃}�l�[�W���[
/// </summary>
class GimmickObjManager
{
public:
    GimmickObjManager();
    GimmickObjManager(ConflictProcesser* conflictProcesser ,CourceDataLoader* courceDataLoader);
    ~GimmickObjManager();
    void Update(float deltaTime);
    void Draw();
private:

    std::list<Actor*> actorList;
    int itemBoxNum = 6;
    const int itemBoxBetween = 25;
    //�ۋ��̃��f��
    int sawModelResource;
    //�A�C�e���{�b�N�X�̃��f��
    int itemBoxModelResource;
    //�ۋ���model�̃A�h���X
    const std::string obstacleModelAddress = "data/model/Saw/Saw.mv1";
    //�A�C�e���{�b�N�X�̃A�h���X
    const std::string itemBoxModelAddress = "data/model/Item/ItemBox/Box.mv1";
};

