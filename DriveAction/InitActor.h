#pragma once
#include <vector>
#include <string>
#include "InitObjKind.h"

//初期化するパラメーター
enum InitObjParamator;
struct ActorParametor;
/// <summary>
/// actorの初期化をする
/// </summary>
class InitActor
{
public:
    InitActor();
    ~InitActor();
    
    ActorParametor GetActorParametor(Init::InitObjKind obj);
private:
    std::vector<std::string> initDataPassFile;
    std::string initActorFileName = "data/model/InitObjPass.csv";
};

/// <summary>
/// 初期化する要素
/// </summary>
enum InitObjParamator
{
    //modelの相対パス
    assetPass = 2,
    //大きさ
    modelSize = 5,
    //最初のポジション
    firstPosY = 8,
    //modelの当たり半径
    collRadius = 11,
    //跳ね返りの大きさ
    bouncePower = 14,
    //構成数
    compositionNum = 17
};
/// <summary>
/// 初期化の際に使う
/// </summary>
struct ActorParametor
{
    float firstPosY;
    float setModelSize;
    float setRadius;
    float setBouncePow;
    std::string modelPass;

};