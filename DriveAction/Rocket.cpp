#include "Rocket.h"

Rocket::Rocket()
{
}

Rocket::Rocket(VECTOR pos, int modelResourceHandle)
{
    position = pos;
    modelHandle = MV1DuplicateModel(modelResourceHandle);
    tag = ObjectTag::damageObject;
    bouncePower = setBouncePower;
}

Rocket::~Rocket()
{

}

void Rocket::Update()
{
    position.y -= fallingSpeed;
    MV1SetPosition(modelHandle,position);
    fallingSpeed += fallingSpeed * gravityPower;
}

void Rocket::Draw()
{
    MV1DrawModel(modelHandle);
}
