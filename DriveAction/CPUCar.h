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
    VECTOR firstPos = { -300.0f,-0.0f,-83.0f };//���[�X�J�n�ʒu
    VECTOR firstDir = { -0.9f,0,-0.02f };//��������
    const float turnProccesLine = 0.4f;//�ړI�n�Ɍ������Ƃ��ɋȂ��邩���f����
};

