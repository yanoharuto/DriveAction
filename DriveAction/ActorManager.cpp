#include "ActorManager.h"

ActorManager::ActorManager()
{
}

ActorManager::~ActorManager()
{
    Actors.clear();
}

void ActorManager::AddActor(Actor& _Actor)
{
    Actors.push_back(_Actor);
}

void ActorManager::UpdateActors()
{
    std::vector<Actor>::iterator Ite;
    Actor actor;
    //アップデートを回す
    for (Ite = Actors.begin(); Ite != Actors.end(); Ite++)
    {
        actor = *Ite;
        //死んでなかったら更新
        if (actor.GetAliveFlag())
        {
            actor.Update();
        }
    }
}

void ActorManager::DrawActors()
{
    std::vector<Actor>::iterator Ite;
    Actor actor;
    for (Ite = Actors.begin(); Ite != Actors.end(); Ite++)
    {
        actor = *Ite;
        actor.Draw();
    }
}
