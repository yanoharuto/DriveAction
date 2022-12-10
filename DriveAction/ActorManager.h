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
    /// 動的配列に追加
    /// </summary>
    /// <param name="_Actor"></param>
    void AddActor(Actor& _Actor);
    /// <summary>
    /// 動的配列で回して更新
    /// </summary>
    void UpdateActors();
    /// <summary>
    /// 動的配列で回して描画
    /// </summary>
    void DrawActors();
private:
    std::vector<Actor> Actors;
};

