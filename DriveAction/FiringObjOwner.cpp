#include "FiringObjOwner.h"

FiringObjOwner::FiringObjOwner()
{
    ownerState = OwnerState::Delete;
    firingPosition = {};
}

FiringObjOwner::~FiringObjOwner()
{
}

void FiringObjOwner::Update(OwnerState state, VECTOR pos)
{
    ownerState = state;
    firingPosition = pos;
}

VECTOR FiringObjOwner::GetPosition()
{
    return firingPosition;
}

OwnerState FiringObjOwner::GetOwnerState()
{
    return ownerState;
}
