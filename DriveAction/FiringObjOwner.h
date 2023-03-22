#pragma once
#include "DxLib.h"
enum class OwnerState
{
    Stop,
    Move,
    Delete
};
class FiringObjOwner
{
public :
    FiringObjOwner();
    ~FiringObjOwner();
    void Update(OwnerState state,VECTOR pos);
    VECTOR GetPosition();
    OwnerState GetOwnerState();
protected:
    OwnerState ownerState;
    VECTOR firingPosition;
};