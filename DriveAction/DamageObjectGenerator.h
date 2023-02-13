#pragma once
#include <string>
#include "ConflictProcesser.h"
#include "AssetManager.h"
#include "FiringItemManager.h"
#include "ItemTag.h"
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
    /// <summary>
    /// �|�C���^��Ⴄ
    /// </summary>
    /// <param name="conflictPro"></param>
    /// <param name="assetMana"></param>
    /// <param name="firingItemMana"></param>
    DamageObjectGenerator(ConflictProcesser* conflictPro, FiringItemManager* firingItemMana);
    ~DamageObjectGenerator();
    /// <summary>
    /// �A�C�e���̎�ނɂ���Đ�������A�C�e����ύX����
    /// </summary>
    /// <param name="itemTag"></param>
    /// <param name="carInfo"></param>
    static void GenerateDamageObject(ItemTag itemTag, ItemArgumentCarInfo carInfo);
private:
};

