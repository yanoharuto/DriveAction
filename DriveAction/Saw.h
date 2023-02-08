#pragma once
#include "Actor.h"
#include "DxLib.h"
/// <summary>
/// è·äQï®Å@Åiä€ÇÃÇ±Åj
/// </summary>
class Saw :
    public Actor
{
public:
    Saw();
    Saw(VECTOR pos, int duplicateModelHandle);
    ~Saw();
    void Update(const float deltaTime) override;
private:
    const float addRotate = 0.02f;
    const float setRadius = 23.0f;
    const float setBouncePower = 4.0f;
};

