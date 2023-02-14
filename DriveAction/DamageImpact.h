#pragma once
#include <string>
#include "DamageObject.h"
/// <summary>
/// ��ѓ���
/// </summary>
class DamageImpact:public DamageObject
{
public:
    DamageImpact();
    /// <summary>
    /// �Ԃ̈ʒu���班�����ꂽ������o�Ă���
    /// </summary>
    /// <param name="carInfo"></param>
    DamageImpact(ItemArgumentCarInfo carInfo);
    ~DamageImpact();
    /// <summary>
    /// �ړ��ƈ�莞�Ԃ��Ə�����
    /// </summary>
    /// <param name="deltaTime"></param>
    void Update(float deltaTime)override;
    /// <summary>
    /// �����ɓ������������
    /// </summary>
    void ConflictProccess() override;
private:
    //��������
    float aliveTime = 0;
    //�ő吶������
    const float setAliveTime = 12.0f;
    //�ړ����x
    const float speed = 400.0f;
    //�����蔻��
    const float setRadius = 2.5f;
    //�A�Z�b�g�̃A�h���X
    const std::string assetAddress = "data/model/Item/SpikeBall/SpikeBall.mv1";
};

