#pragma once
#include "DxLib.h"
#include "ItemTag.h"
/// <summary>
/// �v���C���[��UI����ɕK�v�ȏ��
/// </summary>
struct  PlayerRelatedInfo
{
    //����������
    int lap;
    //����
    int rank;
    //�Ԃ��t�����Ă�����
    bool reverse;
    //�����Ă���A�C�e��
    ItemTag itemTag;
    //����
    float time;
    //���x
    float accelPower;
    //�ő呬�x�ɑ΂��錻�݂̑��x�̊���
    float accelPowerParcent;
};