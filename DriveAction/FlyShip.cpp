#include "FlyShip.h"
#include "DamageObjectGenerator.h"
#include "Utility.h"

FlyShip::FlyShip(Init::InitObjKind kind)
    :Actor(kind)
{
    sub = new ObjectSubject(this);
}

FlyShip::~FlyShip()
{
    SAFE_DELETE(sub);
}

void FlyShip::Update()
{
   
}

