#include "Player.h"

Player::Player()
{
    ModelHandle = MV1LoadModel("data/model/Player/Car Mv1.mv1");
    
}

Player::~Player()
{

}

void Player::Update()
{
}



void Player::Draw()
{
}

VECTOR Player::GetPos()
{
    return Position;
}
