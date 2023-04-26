#pragma once
#include <vector>
#include <string>
enum InitObjKind;
class InitActor
{
public:
    InitActor();
    ~InitActor();
    /// <summary>
    /// èâä˙âªÇÃç€Ç…égÇ§
    /// </summary>
    struct ActorParametor
    {
        float firstPosY;
        float setModelSize;
        std::string modelPass;
    };
    ActorParametor GetActorParametor(InitObjKind obj);
private:
    std::vector<std::string> initData;
    std::string initActorFileName = "data/InitObjPass.csv";

};

enum InitObjKind
{
    player,
    littleRock,
    middleRock,
    bigRock,
    saw,
    bomberShip,
    bomber,
    laserShip,
    laser,
};