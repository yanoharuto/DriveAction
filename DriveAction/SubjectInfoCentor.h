#pragma once
#include "DxLib.h"
#include <unordered_map>
#include "Object.h"

class ObjectSubject;
class ObjectObserver;

class SubjectInfoCentor
{
public :
    SubjectInfoCentor();
    ~SubjectInfoCentor();
    static VECTOR GetDirection(ObjectObserver* observer);
    static VECTOR GetPosition(ObjectObserver* observer);
    static int GetObjTagHitCount(ObjectObserver* observer, Object::ObjectTag objTag);
    static ObjectObserver* GetObjectObserver(ObjectSubject* subject);
protected:
    static std::unordered_map<ObjectObserver*, ObjectSubject*>  subjectMap;
};