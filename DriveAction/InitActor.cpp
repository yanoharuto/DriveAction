#include "InitActor.h"
#include "ListUtility.h"
InitActor::InitActor()
{
    std::vector<std::string> actorDataPassFile = ConvertListToVector(LoadData(initActorFileName));
    for (int i = 0; i < actorDataPassFile.size(); i++)
    {
        if (i % 2 == 1)
        {
            initData.push_back(actorDataPassFile[i]);
        }
    }
}

InitActor::~InitActor()
{
}

InitActor::ActorParametor InitActor::GetActorParametor(InitObjKind objKind)
{
    std::list<std::string> data = LoadData(initData[objKind]);
    ActorParametor param;
    int i = 0;
    for (auto itr = data.begin(); itr != data.end(); itr++)
    {
        switch (i)
        {
        case 0:
            param.firstPosY = atof((*itr).c_str());
            break;
        case 1:
            param.modelPass = (*itr).c_str();
            break;
        case 2:
            param.setModelSize = atof((*itr).c_str());
            break;
        default:
            break;
        }
        i++;
        itr++;
    }

    return param;
}
