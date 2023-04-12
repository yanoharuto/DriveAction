#include "Coin.h"
#include "AssetManager.h"
#include "OriginalMath.h"
#include "Utility.h"
#include "ConflictManager.h"
#include "EffectManager.h"
#include "EffekseerForDXLib.h"
#include "SoundPlayer.h"
//��]��
const float Coin::rotateY = 2.5f;
//�R�T�C���Ŏg��
const float Coin::moveYValue = 0.2f;
//Y�ړ����x
const float Coin::moveYSpeed = 4.0f;
//���a
const float Coin ::setRadius = 46.0f;
//�G�t�F�N�g�̑傫��
const float Coin::effectSize = 4.0f;
//�R�C���̌��ʉ��̃p�X
const std::string Coin::coinSEPass="coin.wav";
//����y���W
const float Coin::firstY = 23.0f; 
//model�̃p�X
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
/// �Ԃ��������̏���
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
