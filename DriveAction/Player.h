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
	Player(VECTOR firstPos,VECTOR firstDir);
	///�f�X�g���N�^
    ~Player();
    /// <summary>
    /// �X�V�i�ړ������j
    /// </summary>
	void Update(const float deltaTime, const bool outsideHitFlag, NeighborhoodInfo neighInfo) override;

private:
	/// <summary>
	/// ���͏�񂩂�i�ތ����Ƒ���������
	/// </summary>
	/// <param name="inputKey">���͏��</param>
	/// <param name="outsideHitFlag">�R�[�X�̊O���ɂԂ��������ǂ���</param>
	/// <returns>���̍X�V�܂łɐi�ތ����Ƒ���</returns>
	VECTOR GetAccelVec(const int inputKey,const bool outsideHitFlag,float deltaTime);
	void Init();
};

