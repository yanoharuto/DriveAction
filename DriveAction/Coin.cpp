#include "Coin.h"
#include "AssetManager.h"
#include "OriginalMath.h"
#include "Utility.h"
#include "ConflictManager.h"
#include "EffectManager.h"
#include "EffekseerForDXLib.h"
#include "SoundPlayer.h"
const float Coin::rotateY = 2.5f;
//コサインで使う
const float Coin::moveYValue = 0.2f;
//Y移動速度
const float Coin::moveYSpeed = 0.8f;
//半径
const float Coin ::setRadius = 46.0f;
//エフェクトの大きさ
const float Coin::effectSize = 4.0f;
//コインの効果音のパス
const std::string Coin::coinSEPass="coin.wav";
//初期y座標
const float Coin::firstY = 18.0f; 
//modelのパス
const std::string Coin::coinPass = "Coin/Coin.mv1";
//エフェクトのパス
const std::string Coin::coinEffectPass= "/coin.efkefc";
Coin::Coin()
{
    modelHandle = AssetManager::GetDuplicate3DModelAssetHandle(coinPass);
    direction = { 1,0,0 };
    collider = new SphereCollider(this);
    EffectManager::LoadEffectManager(coinEffectPass,effectSize);
}

Coin::Coin(VECTOR firstPos)
{
    position = firstPos;
    modelHandle = AssetManager::GetDuplicate3DModelAssetHandle(coinPass);
    direction = { 1,0,0 };
    collider = new SphereCollider(this);
    radius = setRadius;
    EffectManager::LoadEffectManager(coinEffectPass, effectSize);
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
    if (conflictEffect != -1)
    {
        ConflictManager::EraceConflictObjInfo(collider);
        SAFE_DELETE(collider);
        if (IsEffekseer3DEffectPlaying(conflictEffect) == -1)
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
        conflictEffect = EffectManager::GetPlayEffect3D(coinEffectPass);
        SetPosPlayingEffekseer3DEffect(conflictEffect, position.x, position.y, position.z);
        SoundPlayer::Play3DSE(coinSEPass);
    }
}
