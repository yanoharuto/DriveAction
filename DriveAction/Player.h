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
	Player(VECTOR firstPos,VECTOR firstDir,VECTOR destinationPos,SoundPlayer* soundPlayer);
	///�f�X�g���N�^
    ~Player();
    /// <summary>
    /// �X�V�i�ړ������j
    /// </summary>
	void Update(const float deltaTime, const bool outsideHitFlag, NeighborhoodInfo neighInfo,SoundPlayer* soundPlayer) override;

private:
	void Init();

};

