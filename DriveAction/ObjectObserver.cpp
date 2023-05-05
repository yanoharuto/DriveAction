#include "ObjectObserver.h"
#include "SubjectInfoCentor.h"
#include "Object.h"
ObjectObserver::ObjectObserver()
{
}

ObjectObserver::~ObjectObserver()
{
}

VECTOR ObjectObserver::GetSubPos()
{
    return SubjectInfoCentor::GetPosition(this);
}

VECTOR ObjectObserver::GetSubDir()
{
    return SubjectInfoCentor::GetDirection(this);
}

int ObjectObserver::GetObjHitCount(Object::ObjectTag objTag)
{
    return SubjectInfoCentor::GetObjTagHitCount(this,objTag);
}
