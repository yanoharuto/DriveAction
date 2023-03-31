#pragma once
#include "FiringObjOwner.h"
#include "RotatingLasers.h"
class BigRadiusLaser:public RotatingLasers
{
public:
    BigRadiusLaser(FiringObjOwner* setOwner);

    /// <summary>
/// ��]������
/// </summary>
/// <param name="deltaTime"></param>
    void Update()override;

private:
    //���[�U�[�G�t�F�N�g�̃p�X
    static const InitParam initParam;
    
    //��]���x
    static const float rotaSpeed;
    FiringObjOwner* owner;
};

