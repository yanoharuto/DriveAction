#include "ObjectSubject.h"
#include "ConflictProccesor.h"
/// <summary>
/// �Ď�����鑤
/// </summary>
/// <param name="obj"></param>
/// <param name="addDataFileName"></param>
ObjectSubject::ObjectSubject(Object* obj )
{
    subCollider = nullptr;
    subObject = obj;
}

ObjectSubject::ObjectSubject(Object* setObj, ConflictProccesor* setConProccesor)
{
    subObject = setObj;
    subCollider = setConProccesor;
}

ObjectSubject::~ObjectSubject()
{
}

VECTOR ObjectSubject::GetObjPos()
{
    return subObject->GetPos();
}

VECTOR ObjectSubject::GetObjDir()
{
    return subObject->GetDir();
}

Object::ObjectTag ObjectSubject::GetObjTag()
{
    return subObject->GetTag();
}

int ObjectSubject::GetTagObjectHitCount(Object::ObjectTag hitObjTag)
{
    return subCollider->GetTagHitCount(hitObjTag);
}