#include "InitActor.h"
#include "CSVFileLoader.h"
#include "Utility.h"
#include "InitObjKind.h"
InitActor::InitActor()
{
    CSVFileLoader* initDataLoader = new CSVFileLoader(initActorFileName);
    initDataPassFile = initDataLoader->GetLoadData();
    SAFE_DELETE(initDataLoader);
}

InitActor::~InitActor()
{
}

ActorParametor InitActor::GetActorParametor(Init::InitObjKind objKind)
{
    int num = static_cast<int>(objKind);

    //ÉfÅ[É^ì«Ç›éÊÇË
    CSVFileLoader* initDataLoader = new CSVFileLoader(initDataPassFile[num]);
    std::vector<std::string> initData = initDataLoader->GetLoadData();
    ActorParametor param = {};
    param.firstPosY = atof(initData[InitObjParamator::firstPosY].c_str());
    param.modelPass = initData[InitObjParamator::assetPass];
    param.setModelSize = atof(initData[InitObjParamator::modelSize].c_str());
    param.setBouncePow = atof(initData[InitObjParamator::bouncePower ].c_str());
    param.setRadius = atof(initData[InitObjParamator::collRadius].c_str());
    SAFE_DELETE(initDataLoader);
    return param;
}
