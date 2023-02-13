#pragma once
#include <string>
#include "Item.h"

/// <summary>
/// ���e������тȂ���΂�܂�
/// </summary>
class Kite :
    public ItemBase
{
public:
    Kite();
    ~Kite();
	/// <summary>
	/// ���ʏI���܂ŏ㏸����
	/// </summary>
	/// <param name="deltaTime"></param>
	/// <param name="carInfo"></param>
	void Update(float deltaTime,ItemArgumentCarInfo carInfo)override;
    /// <summary>
    /// �㏸���邽�߂̃��P�b�g�o������t����
    /// </summary>
    void Draw()override;
    /// <summary>
    /// ���e�𔭎�
    /// </summary>
    /// <param name="carInfo"></param>
    void ShowEffect(ItemArgumentCarInfo carInfo)override;
private:
    void SetMatrix(int modelH, ItemArgumentCarInfo carInfo,VECTOR addPos);
    //���ʎ���
    const float setEffecacyTime = 4.2f;
    //���e���΂�܂��Ԋu
	const float setCoolTime = 0.28f;
    //����ԗ�
	const float flyPower = 14.3f;
    //�ő卂�x
	const float maxHeight = 13.0f;
    //�RDmodel�̃A�h���X
    const std::string modelAddress = "data/model/Item/Rocket/Rocket06_Green.mv1";
    int leftRocketModelHandle;
};