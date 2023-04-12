#include "Coin.h"
#include "AssetManager.h"
#include "OriginalMath.h"
#include "Utility.h"
#include "ConflictManager.h"
#include "EffectManager.h"
#include "EffekseerForDXLib.h"
#include "SoundPlayer.h"
//回転量
const float Coin::rotateY = 2.5f;
//コサインで使う
const float Coin::moveYValue = 0.2f;
//Y移動速度
const float Coin::moveYSpeed = 4.0f;
//半径
const float Coin ::setRadius = 46.0f;
//エフェクトの大きさ
const float Coin::effectSize = 4.0f;
//コインの効果音のパス
const std::string Coin::coinSEPass="coin.wav";
//初期y座標
const float Coin::firstY = 23.0f; 
//modelのパス
const std::string Coin::coinPass = "Coin/Coin.mv1";
Coin::Coin()
{
    modelHandle = AssetManager::Get3DModelAssetHandle(coinPass);
    direction = { 1,0,0 };
    collider = new SphereCollider(this);
}

Coin::Coin(VECTOR firstPos)
{
    position = firstPos;
    modelHandle = AssetManager::Get3DModelAssetHandle(coinPass);
    direction = { 1,0,0 };
    collider = new SphereCollider(this);
    radius = setRadius;
    SoundPlayer::LoadSound(coinSEPass);
    tag = ObjectTag::coin;
}

Coin::~Coin()
{
    ConflictManager::EraceConflictObjInfo(collider);
    SAFE_DELETE(collider);
}

void Coin::Update()
{
    direction = VNorm(OriginalMath::GetYRotateVector(direction, rotateY));
    totalMoveYValue += moveYValue;
    position.y = firstY + cosf(totalMoveYValue) * moveYSpeed;
    if (isCarConflict == true)
    {
        ConflictManager::EraceConflictObjInfo(collider);
        SAFE_DELETE(collider);
        if(!SoundPlayer::IsPlaySound(coinSEPass))
        {
            aliveFlag = false;
        }
    }
}
/// <summary>
/// ぶつかった時の処理
/// </summary>
/// <param name="conflictInfo"></param>
void Coin::ConflictProccess(const ConflictExamineResultInfo conflictInfo)
{
    if (conflictInfo.tag == ObjectTag::countSystem)
    {
       SoundPlayer::Play3DSE(coinSEPass);
       isCarConflict = true;
    }
}
