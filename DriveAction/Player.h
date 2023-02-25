#pragma once
#include "Racer.h"
#include "PlayerCar.h"
#include "PlayerRelatedInfo.h"
#include "PlaySceneCamaeraArgumentInfo.h"
/// <summary>
/// プレイヤーの車やアイテムの処理を呼び出す
/// </summary>
class Player final:
    public Racer 
{
public:
    Player();
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="circuitData"></param>
    /// <param name="firstPos"></param>
    /// <param name="firstDir"></param>
    Player(VECTOR firstPos, int duplicateModel);
    ~Player();
    /// <summary>
    /// プレイヤーの更新処理
    /// </summary>
    /// <param name="deltaTime"></param>
    /// <param name="outsideHitFlag"></param>
    /// <param name="damageObjGene"></param>
    void Update(float deltaTime, bool outsideHitFlag, DamageObjectGenerator* damageObjGene)override;
    /// <summary>
    /// プレイヤーの周辺情報を返す
    /// </summary>
    /// <returns></returns>
    PlayerRelatedInfo GetRelatedInfo();
    /// <summary>
    /// カメラに渡したい情報を返す
    /// </summary>
    /// <returns></returns>
    PlaySceneCameraArgumentInfo GetCameraArgumentInfo();
private:
    PlayerCar* playerCar = nullptr;
    std::string rouletteSE = "rourette.mp3";
    float setHP = 100;
};

