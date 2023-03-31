#include "Coin.h"
#include "AssetManager.h"
#include "OriginalMath.h"
#include "Utility.h"
#include "ConflictManager.h"
#include "EffectManager.h"
#include "EffekseerForDXLib.h"
#include "SoundPlayer.h"
const float Coin::rotateY = 2.5f;
//�R�T�C���Ŏg��
const float Coin::moveYValue = 0.2f;
//Y�ړ����x
const float Coin::moveYSpeed = 0.8f;
//���a
const float Coin ::setRadius = 46.0f;
//�G�t�F�N�g�̑傫��
const float Coin::effectSize = 4.0f;
//�R�C���̌��ʉ��̃p�X
const std::string Coin::coinSEPass="coin.wav";
//����y���W
const float Coin::firstY = 18.0f; 
//model�̃p�X
const std::string Coin::coinPass = "Coin/Coin.mv1";
//�G�t�F�N�g�̃p�X
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
/// �Ԃ��������̏���
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
