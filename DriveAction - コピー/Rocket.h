#pragma once
#include<string>
#include "DamageObject.h"
#include "ItemArgumentCarInfo.h"
#include "DxLib.h"

class Rocket final :public DamageObject
{
public:
    Rocket() {};
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="carInfo"></param>
    Rocket(ItemArgumentCarInfo carInfo);
    ~Rocket();
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name="deltaTime"></param>
    void Update(float deltaTime)override;
    /// <summary>
    /// �Փˌ�̏���
    /// </summary>
    void ConflictProccess()override;
private:
    //���P�b�g�̃��f���̃A�h���X
    const std::string rocketModelAddress = "Item/Rocket/Rocket04_Grey.mv1";
    const std::string effectAddress = "bomb.efkefc";
    //�������x
    float fallingSpeed = 24.5f;
    //�͂����Ԃ���
    float setBouncePower = 4.25f;
    //�d��
    const float gravityPower = 0.9f;
    //���P�b�g�̃T�C�Y
    const float setSize = 1.000f;
    //���a
    const float setRadius = 3.25f;
    //�����Ă���G�t�F�N�g
    int playEffect = -1;
    //�n�ʂɐG��Ă��邩
    bool onGround = false;
};

