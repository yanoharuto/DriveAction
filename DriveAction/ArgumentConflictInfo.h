#pragma once
#include "DxLib.h"
#include "ObjectTagEnum.h"
#include "Object.h"
/// <summary>
/// �����蔻��Ŏg�������ɂ��ēn���������
/// </summary>
struct ArgumentConflictInfo
{
    bool hitFlag = false;//�����蔻��œ���������
    ObjectTag tag = ObjectTag::obstacle;//�I�u�W�F�N�g�̃^�O
    VECTOR pos = {};//�|�W�V����
    VECTOR dir = {};//�����Ă����
    float radius = 0;//���a
    /// <summary>
    /// �����̃I�u�W�F�N�g��������쐬
    /// </summary>
    /// <param name="hit">�����蔻��œ���������</param>
    /// <param name="obj">��肽�����̃I�u�W�F�N�g</param>
    void SetObjInfo(bool hit,Object* const obj)
    {
        hitFlag = hit;
        tag = obj->GetTag();
        pos = obj->GetPos();
        dir = obj->GetDir();
        radius = obj->GetRadius();
    }
};