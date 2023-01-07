#pragma once
#include "Car.h"
/// <summary>
/// �����^�]�̎�
/// </summary>
class CPUCar :
    public Car
{
public:
    CPUCar();
    CPUCar(VECTOR firstPos,VECTOR firstDir);
    ~CPUCar();
    void Update(const float deltaTime,const bool outsideHitFlag)override;
    
private:
    /// <summary>
    /// �R���s���[�^�[�ŉ�������
    /// </summary>
    /// <param name="dir">����������</param>
    /// <param name="outsideHitFlag">�R�[�X�O�ɂԂ�������</param>
    /// <returns></returns>
    VECTOR GetAccelVec(const float dir,const bool outsideHitFlag);
    void Init();
    const float turnProccesLine = 0.3f;//�ړI�n�Ɍ������Ƃ��ɋȂ��邩���f����
};

