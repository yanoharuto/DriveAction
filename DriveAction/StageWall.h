#pragma once
#include "Actor.h"
#include "WallCollider.h"
/// <summary>
/// �s���͈͂����߂��
/// </summary>
class StageWall:public Actor
{
public:
    /// <summary>
    /// �s���͈͂����߂��
    /// </summary>
    StageWall();
    //�����蔻�������
    ~StageWall();
private:
    //�ǂ�model�p�X
    const std::string modelFilePass = "Stage/StageWall.mv1";
    //�t����΂���
    const float setBouncePower = 20;
    //������Ɩ��܂��Ă邩���ɍs��
    VECTOR setFirstPos = { 0,100.0f,0 };
    //�s���͈�
    WallCollider* wallCollider;
    //�}�b�v�̒[�P
    VECTOR stageBiggestSize = { -3200,0,-3200 };
    //�}�b�v�̒[2
    VECTOR stageSmallestSize = { 2600,0,2600 };
};
