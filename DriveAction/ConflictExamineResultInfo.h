#pragma once
#include "DxLib.h"
#include "ObjectTagEnum.h"
#include "Object.h"
/// <summary>
/// �����蔻��̌��ʂŏo������
/// </summary>
struct ConflictExamineResultInfo
{
    bool hitFlag = false;//�����蔻��œ���������
    ObjectTag tag = ObjectTag::obstacle;//�I�u�W�F�N�g�̃^�O
    VECTOR bounceVec = {};
    VECTOR pos = {};
    float radius = 0;//���a
    float bouncePower;//������
    /// <summary>
    /// �����̃I�u�W�F�N�g��������쐬
    /// </summary>
    /// <param name="hit">�����蔻��œ���������</param>
    /// <param name="obj">��肽�����̃I�u�W�F�N�g</param>
    void SetObjInfo(Object* const obj)
    {
        tag = obj->GetTag();
        radius = obj->GetRadius();
        bouncePower = obj->GetBouncePower();
    }
};