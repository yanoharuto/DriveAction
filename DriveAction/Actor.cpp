#include "Object.h"
#include "Actor.h"
#include "HitChecker.h"
#include "OriginalMath.h"
#include "InitActor.h"

#include "AssetManager.h"
Actor::Actor()

    :modelHandle(-1),
    velocity({})
{
}
Actor::Actor(Init::InitObjKind kind)
{
    InitActor* init = new InitActor();
    ActorParametor initParam = init->GetActorParametor(kind);
    //�A�Z�b�g�������Ă���
    modelHandle = AssetManager::Get3DModelAssetHandle(initParam.modelPass.c_str());
    //�|�W�V����
    position.y = initParam.firstPosY;
    //���˕Ԃ��
    bouncePower = initParam.setBouncePow;
    //���a
    radius = initParam.setRadius;
    //model�̑傫��
    modelSize = initParam.setModelSize;
};

void Actor::Draw()
{
    if (modelHandle != -1)
    {
        //�ύX�O�̍s���ۑ�
        MATRIX tmpMat = MV1GetMatrix(modelHandle);
        //������ς���
        ModelSetMatrix();
        //�|�W�V�����ύX
        UpdateMV1Pos();
        //�T�C�Y�ύX
        MV1SetScale(modelHandle, VGet(modelSize, modelSize, modelSize));
        MV1DrawModel(modelHandle);
        //�s������ɖ߂�
        MV1SetRotationMatrix(modelHandle, tmpMat);
    }
}

VECTOR Actor::GetVelocity()
{

    return velocity;

}

HitCheckExamineObjectInfo Actor::GetHitCheckExamineInfo()
{
    HitCheckExamineObjectInfo objInfo;
    objInfo.SetExamineInfo(this);
    objInfo.velocity = velocity;
    return objInfo;
}

ArgumentConflictResultInfo Actor::GetConflictArgumentInfo()
{
    ArgumentConflictResultInfo resultInfo;
    resultInfo.SetObjInfo(this);
    return resultInfo;
}

void Actor::ModelSetMatrix()
{
    // �����ɍ��킹�ĉ�].
    MV1SetRotationZYAxis(modelHandle, direction, VGet(0.0f, 1.0f, 0.0f), 0.0f);

    MATRIX tmpMat = MV1GetMatrix(modelHandle);
    // ���f���Ɍ����Ăق��������ɉ�].
    MATRIX rotYMat = MGetRotY(180.0f * RAGE);
    tmpMat = MMult(tmpMat, rotYMat);
    MV1SetRotationMatrix(modelHandle, tmpMat);
}

void Actor::UpdateMV1Pos()
{
    // �͂������I������x���V�e�B�̕����Ƀf�B���N�V�����𒲐�.
    if (VSize(velocity) != 0)
    {
        direction = VNorm(velocity);
    }
    // �|�W�V�������X�V.
    position = VAdd(position, velocity);
    // �RD���f���̃|�W�V�����ݒ�
    MV1SetPosition(modelHandle, position);
}
