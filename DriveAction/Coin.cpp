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
/// <summary>
/// 初期化
/// </summary>
/// <param name="firstPos"></param>
Coin::Coin(VECTOR firstPos)
{
    position = firstPos;
    modelHandle = AssetManager::Get3DModelAssetHandle(coinPass);
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
/// くるくる回転
/// </summary>
void Coin::Update(ObjInfo info)
{

    //向きを変更
    direction = VNorm(OriginalMath::GetYRotateVector(direction, rotateY));
    totalMoveYValue += moveYValue;
    //ちょっと上下に動く
    position.y = firstY + cosf(totalMoveYValue) * moveYSpeed;
    //車にぶつかってたら効果音を出して終了
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

void Coin::Draw()
{
    VECTOR lightDir = GetLightDirection();
    VECTOR lightPos = position;
    lightPos.y += 300;
    ChangeLightTypeSpot(lightPos, VGet(0, -1.0f, 0), DX_PI_F / 2, DX_PI_F / 4, 2000.0f, 0.0f, 0.008f, 0.0f);

    MATRIX tmpMat = MV1GetMatrix(modelHandle);
    if (modelHandle != -1)
    {
        ModelSetMatrix();
        UpdateMV1Pos();
        MV1SetScale(modelHandle, VGet(modelSize, modelSize, modelSize));
        MV1DrawModel(modelHandle);
    }
    //行列を元に戻す
    MV1SetRotationMatrix(modelHandle, tmpMat);

    ChangeLightTypeDir(lightDir);
}