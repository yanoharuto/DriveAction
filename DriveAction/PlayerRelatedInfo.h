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
    //�Ԃ̌���
    VECTOR carDirection;
    //�Ԃ̎��Ɍ������ꏊ�̌���
    VECTOR nextCheckPointDirection;
    //�����Ă���A�C�e��
    ItemTag itemTag;
    //����
    float time;
    //���x
    float accelPower;
};