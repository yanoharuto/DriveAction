#pragma once
#include "Item.h"
#include "ConflictProcesser.h"
#include "DamageObjectGenerator.h"
/// <summary>
/// �A�C�e���𐶐����Ďg����悤�ɂ���
/// </summary>
class ItemHolder
{
public:
    ItemHolder();
    ~ItemHolder();
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name="damageObjeGene"></param>
    /// <param name="carInfo"></param>
    /// <param name="deltaTime"></param>
    void Update(DamageObjectGenerator* damageObjeGene,ItemArgumentCarInfo carInfo,float deltaTime);
    /// <summary>
    /// �A�C�e��������
    /// </summary>
    /// <param name="rank"></param>
    void SelectItem(int rank);
    /// <summary>
    /// �A�C�e�����g�p
    /// </summary>
    void UseItem(ItemArgumentCarInfo carInfo);
    /// <summary>
    /// �A�C�e���̕`��
    /// </summary>
    void ItemDraw();
    /// <summary>
    /// �A�C�e���̏���n��
    /// </summary>
    /// <returns>�����A�C�e���������ĂȂ��Ȃ�Tag��non</returns>
    ItemInfo GetItemInfo();

private:
    ItemBase* item;
    float rouletteTime = -1;
    const float setRouletteTime = 2.5f;
    bool roulette = false;
};