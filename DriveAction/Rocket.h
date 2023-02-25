#pragma once
#include<string>
#include "DamageObject.h"
#include "ItemArgumentCarInfo.h"
#include "DxLib.h"

class Rocket final :public DamageObject
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
    void Update(float deltaTime)override;
    /// <summary>
    /// 衝突後の処理
    /// </summary>
    void ConflictProccess()override;
private:
    //ロケットのモデルのアドレス
    const std::string rocketModelAddress = "Item/Rocket/Rocket04_Grey.mv1";
    const std::string effectAddress = "bomb.efkefc";
    //落下速度
    float fallingSpeed = 24.5f;
    //はじき返す力
    float setBouncePower = 4.25f;
    //重力
    const float gravityPower = 0.9f;
    //ロケットのサイズ
    const float setSize = 1.000f;
    //半径
    const float setRadius = 3.25f;
    //動いているエフェクト
    int playEffect = -1;
    //地面に触れているか
    bool onGround = false;
};

