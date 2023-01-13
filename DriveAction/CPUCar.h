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
    void Update(float deltaTime,bool outsideHitFlag)override;
    
private:
    /// <summary>
    /// �R���s���[�^�[�ŉ�������
    /// </summary>
    /// <param name="dir">����������</param>
    /// <param name="outsideHitFlag">�R�[�X�O�ɂԂ�������</param>
    /// <returns></returns>
    VECTOR GetAccelVec(HandleDirection handleDir ,bool outsideHitFlag,float deltaTime);
    void Init();
    const float turnProccesLine = 7.0f;//�ړI�n�Ɍ������Ƃ��ɋȂ��邩���f����
};

