#pragma once
#include <string>
#include "ItemTag.h"
#include "FiringObjOwner.h"
#include "ItemArgumentCarInfo.h"

/// <summary>
/// �����A�C�e���Ȃǂ̃_���[�W������I�u�W�F�N�g�𐶐�����
/// </summary>
class DamageObjectGenerator
{
public:
    /// <summary>
    /// �f�t�H���g�R���X�g���N�^
    /// </summary>
    DamageObjectGenerator();
    ~DamageObjectGenerator();
    /// <summary>
    /// �A�C�e���̎�ނɂ���Đ�������A�C�e����ύX����
    /// </summary>
    /// <param name="itemTag"></param>
    /// <param name="carInfo"></param>
    static Actor* GenerateDamageObject(ItemTag itemTag, ItemArgumentCarInfo carInfo,FiringObjOwner* owner);
};