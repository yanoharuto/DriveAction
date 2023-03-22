#include "RotatingLasers.h"
#include "EffectManager.h"
#include "EffekseerForDXLib.h"
#include "OriginalMath.h"
#include "ConflictManager.h"
#include "Utility.h"
//�ŏ��̉�]����
const VECTOR RotatingLasers::firstDir = { 0.0f,0.0f,-1.0f };
//��]���x
const float RotatingLasers::rotaSpeed = 81.0f;
//���[�U�[�̒��S����̋���
const float RotatingLasers::laserRange = 130.0f;
//���[�U�[�̑���
const float RotatingLasers::setRadius = 12.0f;
//�����鍂�x
const float RotatingLasers::conflictY = 6.0f;
/// <summary>
/// ������
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
        //�ړ����Ă�����ꏊ�ύX
        VECTOR pos = owner->GetPosition();
        SetPosPlayingEffekseer3DEffect(playEffect,pos.x,pos.y,pos.z);

        //�����ύX�@�G�t�F�N�g�̌�����ς���
        direction = VNorm(OriginalMath::GetYRotateVector(direction, rotaSpeed * deltaTime));
        effectRota -= rotaSpeed * deltaTime * RAGE;
        SetRotationPlayingEffekseer3DEffect(playEffect, 0, effectRota, 0);
        //�����蔻����ύX
        position = VAdd(pos, VScale(direction, laserRange));
        position.y = conflictY;
    }
}