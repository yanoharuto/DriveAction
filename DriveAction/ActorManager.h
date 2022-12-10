#pragma once
#include "Actor.h"
#include <iostream>
#include <vector>
class ActorManager
{
public:
    ActorManager();
    ~ActorManager();
    /// <summary>
    /// ���I�z��ɒǉ�
    /// </summary>
    /// <param name="_Actor"></param>
    void AddActor(Actor& _Actor);
    /// <summary>
    /// ���I�z��ŉ񂵂čX�V
    /// </summary>
    void UpdateActors();
    /// <summary>
    /// ���I�z��ŉ񂵂ĕ`��
    /// </summary>
    void DrawActors();
private:
    std::vector<Actor> Actors;
};

