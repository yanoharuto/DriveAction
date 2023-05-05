#include "SubjectInfoCentor.h"
#include "ObjectObserver.h"
#include "ObjectSubject.h"
#include "Utility.h"

std::unordered_map<ObjectObserver*, ObjectSubject*> SubjectInfoCentor:: subjectMap;
SubjectInfoCentor::SubjectInfoCentor()
{
    subjectMap.clear();
}

SubjectInfoCentor::~SubjectInfoCentor()
{
    subjectMap.clear();
}

VECTOR SubjectInfoCentor::GetPosition(ObjectObserver* observer)
{
    return subjectMap[observer]->GetObjPos();
}

int SubjectInfoCentor::GetObjTagHitCount(ObjectObserver* observer, Object::ObjectTag objTag)
{
    return subjectMap[observer]->GetTagObjectHitCount(objTag);
}

VECTOR SubjectInfoCentor::GetDirection(ObjectObserver* observer)
{
    return subjectMap[observer]->GetObjDir();
}

ObjectObserver* SubjectInfoCentor::GetObjectObserver(ObjectSubject* subject)
{
    ObjectObserver* observer;
    for (auto itr = subjectMap.begin(); itr != subjectMap.end(); itr++)
    {
        if ((*itr).second == subject)
        {
            return (*itr).first;
        }
    }
    observer = new ObjectObserver();
    subjectMap.insert(std::make_pair(observer,subject));
    return observer;
}