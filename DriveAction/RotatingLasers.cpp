#include "RotatingLasers.h"
#include "EffectManager.h"
#include "EffekseerForDXLib.h"
#include "OriginalMath.h"
#include "ConflictManager.h"
#include "Utility.h"
//最初の回転方向
const VECTOR RotatingLasers::firstDir = { 0.0f,0.0f,-1.0f };
//回転速度
const float RotatingLasers::rotaSpeed = 81.0f;
//レーザーの中心からの距離
const float RotatingLasers::laserRange = 130.0f;
//レーザーの太さ
const float RotatingLasers::setRadius = 12.0f;
//当たる高度
const float RotatingLasers::conflictY = 6.0f;
/// <summary>
/// 初期化
/// </summary>
/// <param name="setOwner"></param>
RotatingLasers::RotatingLasers(FiringObjOwner* setOwner)
{
    position = setOwner->GetPosition();
    firstPos = position;
    owner = setOwner;
    tag = ObjectTag::damageObject;
    EffectManager::LoadEffectManager(laserEffectAddress, 120.0f);
    playEffect = EffectManager::GetPlayEffect3D(laserEffectAddress);

    SetPosPlayingEffekseer3DEffect(playEffect, position.x,position.y,position.z);
    direction = firstDir;
    radius = setRadius;
    bouncePower = 0;
    collider = new SphereCollider(this);
}

RotatingLasers::~RotatingLasers()
{
    StopEffekseer3DEffect(playEffect);
    ConflictManager::EraceConflictObjInfo(collider);
    SAFE_DELETE(collider);
}

void RotatingLasers::Update(float deltaTime)
{
    if (owner->GetOwnerState() != OwnerState::Delete)
    {
        //移動していたら場所変更
        VECTOR pos = owner->GetPosition();
        SetPosPlayingEffekseer3DEffect(playEffect,pos.x,pos.y,pos.z);

        //方向変更　エフェクトの向きを変える
        direction = VNorm(OriginalMath::GetYRotateVector(direction, rotaSpeed * deltaTime));
        effectRota -= rotaSpeed * deltaTime * RAGE;
        SetRotationPlayingEffekseer3DEffect(playEffect, 0, effectRota, 0);
        //当たり判定も変更
        position = VAdd(pos, VScale(direction, laserRange));
        position.y = conflictY;
    }
}