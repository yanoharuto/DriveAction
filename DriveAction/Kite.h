#pragma once
#include "Item.h"
/// <summary>
/// ”š’e‚ð‹ó‚ð”ò‚Ñ‚È‚ª‚ç‚Î‚ç‚Ü‚­
/// </summary>
class Kite :
    public Item
{
public:
    Kite();
    ~Kite();
	void Update(float deltaTime)override;
	void ShowEffect()override;
private:
    const float setEffecacyTime = 4.2f;
	const float setCoolTime = 0.28f;
	const float flyPower = 14.3f;
	const float maxHeight = 24.0f;
};