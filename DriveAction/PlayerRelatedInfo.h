#pragma once
#include "DxLib.h"
#include "ItemTag.h"
#include "ObjPosAndDir.h"
/// <summary>
/// �v���C���[��UI����ɕK�v�ȏ��
/// </summary>
struct  PlayerRelatedInfo
{
    //����������
    int lap;
    //����
    int rank;
    //�`�F�b�N�|�C���g�ʉ߂�����
    int transitCount;
    //����������
    int damageObjHitCount;
    //�R�C�������������
    int hitCoinCount;
    //�Ԃ��t�����Ă�����
    bool isReverseDrive;
    //����ł��邩
    bool isAlive;
    //�����Ă���A�C�e��
    ItemTag itemTag;
    //�o�ߎ���
    float scoreTime;
    //���x
    float accelPower;
    //�ő呬�x�ɑ΂��錻�݂̑��x�̊���
    float accelPowerParcent;

    //�ʒu�Ƃ������Ƃ��傫��
    ObjInfo objInfo;
};