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
    //�A�b�v�f�[�g����
    for (Ite = Actors.begin(); Ite != Actors.end(); Ite++)
    {
        actor = *Ite;
        //����łȂ�������X�V
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
