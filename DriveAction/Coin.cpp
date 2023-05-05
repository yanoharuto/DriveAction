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
/// <summary>
/// ������
/// </summary>
/// <param name="firstPos"></param>
Coin::Coin(VECTOR firstPos)
    :Actor(Init::coin)
{
    position = firstPos;
    direction = { 1,0,0 };
    collider = new SphereCollider(this);
    radius = setRadius;
    SoundPlayer::LoadSound(coinSEPass);
    tag = ObjectTag::coin;
    firstPos.y += radius;
}

Coin::~Coin()
{
    ConflictManager::EraceConflictObjInfo(collider);
    SAFE_DELETE(collider);
}
/// <summary>
/// ���邭���]
/// </summary>
void Coin::Update()
{
    //������ύX
    direction = VNorm(OriginalMath::GetYRotateVector(direction, rotateY));
    totalMoveYValue += moveYValue;
    //������Ə㉺�ɓ���
    position.y = firstY + cosf(totalMoveYValue) * moveYSpeed;
    //�ԂɂԂ����Ă�����ʉ����o���ďI��
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

void Coin::Draw()
{/*
    VECTOR lightDir = GetLightDirection();
    VECTOR lightPos = position;
    lightPos.y += 300;
    ChangeLightTypeSpot(lightPos, VGet(0, -1.0f, 0), DX_PI_F / 2, DX_PI_F / 4, 2000.0f, 0.0f, 0.008f, 0.0f);*/

    MATRIX tmpMat = MV1GetMatrix(modelHandle);
    if (modelHandle != -1)
    {
        ModelSetMatrix();
        UpdateMV1Pos();
        MV1SetScale(modelHandle, VGet(modelSize, modelSize, modelSize));
        MV1DrawModel(modelHandle);
    }
    //�s������ɖ߂�
    MV1SetRotationMatrix(modelHandle, tmpMat);

   // ChangeLightTypeDir(lightDir);
}