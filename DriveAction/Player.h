#pragma once
#include "Car.h"
class Wheels;
 /// <summary>
 /// �v���C���[(��)
 /// </summary>
 class Player final: public Car
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <returns></returns>
	Player();
	///�f�X�g���N�^
    ~Player();
    /// <summary>
    /// �X�V�i�ړ������j
    /// </summary>
    void Update(const float deltaTime,const bool outsideHitFlag) override;
    /// <summary>
    /// �`��
    /// </summary>
    void Draw() override;
private:
	/// <summary>
	/// ���͏�񂩂�i�ތ����Ƒ���������
	/// </summary>
	/// <param name="inputKey">���͏��</param>
	/// <param name="outsideHitFlag">�R�[�X�̊O���ɂԂ��������ǂ���</param>
	/// <returns>���̍X�V�܂łɐi�ތ����Ƒ���</returns>
	VECTOR GetAccelVec(const int inputKey,const bool outsideHitFlag);
	//todo �R���X�g���N�^�ň����ŕύX�ł���悤�ɂ���
	VECTOR firstPos = { -300.0f,-0.0f,-83.0f };//���[�X�J�n�ʒu
	VECTOR firstDir = { -0.9f,0,-0.02f };//��������
};

