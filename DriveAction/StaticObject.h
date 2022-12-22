#pragma once
#include "DxLib.h"
/// <summary>
/// �A�b�v�f�[�g���Ȃ��Ă����I�u�W�F�N�g
/// </summary>
class StaticObject
{
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <returns></returns>
    StaticObject()
        :modelHandele(-1),
        position({}),
        scale({})
    {}
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    /// <returns></returns>
    virtual ~StaticObject() {}
    /// <summary>
    /// �`��
    /// </summary>
    virtual void Draw() {}
protected:
    int modelHandele;
    VECTOR position;
    VECTOR scale;
};