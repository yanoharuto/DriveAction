#pragma once
#include<string>
#include "Actor.h"
#include "ItemArgumentCarInfo.h"
#include "DxLib.h"
#include "SphereCollider.h"
/// <summary>
/// 上から下に落とす爆弾
/// </summary>
class Rocket final :public Actor
{
public:
    Rocket() {};
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="carInfo"></param>
    Rocket(ItemArgumentCarInfo carInfo);
    ~Rocket();
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name="deltaTime"></param>
    void Update()override;
    /// <summary>
    /// 衝突後の処理
    /// </summary>
    void ConflictProccess(ConflictExamineResultInfo resultInfo)override;
private:
    //ロケットのモデルのアドレス
    static const std::string rocketModelPass;
    //エフェクトのmodelのアドレス
    static const std::string effectPass;
    //最初の落下速度
    static const float setFallingSpeed;
    //落下速度
    float fallingSpeed = setFallingSpeed;
    //はじき返す力
    static const float setBouncePower;
    //重力
    static const float gravityPower;
    //ロケットのサイズ
    static const float setModelSize;
    //エフェクトのサイズ
    static const float setEffectSize;
    //当たり判定の大きさ
    static const float setRadius;
    //燃えた時の当たり判定の大きさ
    static const float setBurnRadius;
    //動いているエフェクト
    int burnEffect = -1;
    //地面に触れているか
    bool onGround = false;
    //当たり判定
    SphereCollider* collider = nullptr;
};