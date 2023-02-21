#pragma once
#include "Car.h"
class Wheels;
 /// <summary>
 /// �v���C���[(��)
 /// </summary>
 class PlayerCar final: public Car
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <returns></returns>
	PlayerCar();
	PlayerCar(VECTOR firstPos,VECTOR firstDir,VECTOR destinationPos, int duplicateModelHandle);
	///�f�X�g���N�^
    ~PlayerCar();
    /// <summary>
    /// �X�V�i�ړ������j
    /// </summary>
	void Update(const float deltaTime, const bool outsideHitFlag,ItemInfo itemInfo) override;
	HandleDirection GetHandleDirection();
private:
	void SetInputDir();
};