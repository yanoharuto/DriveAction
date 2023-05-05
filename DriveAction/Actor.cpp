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
    //アセットを持ってくる
    modelHandle = AssetManager::Get3DModelAssetHandle(initParam.modelPass.c_str());
    //ポジション
    position.y = initParam.firstPosY;
    //跳ね返り力
    bouncePower = initParam.setBouncePow;
    //半径
    radius = initParam.setRadius;
    //modelの大きさ
    modelSize = initParam.setModelSize;
};

void Actor::Draw()
{
    if (modelHandle != -1)
    {
        //変更前の行列を保存
        MATRIX tmpMat = MV1GetMatrix(modelHandle);
        //向きを変える
        ModelSetMatrix();
        //ポジション変更
        UpdateMV1Pos();
        //サイズ変更
        MV1SetScale(modelHandle, VGet(modelSize, modelSize, modelSize));
        MV1DrawModel(modelHandle);
        //行列を元に戻す
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
    // 向きに合わせて回転.
    MV1SetRotationZYAxis(modelHandle, direction, VGet(0.0f, 1.0f, 0.0f), 0.0f);

    MATRIX tmpMat = MV1GetMatrix(modelHandle);
    // モデルに向いてほしい方向に回転.
    MATRIX rotYMat = MGetRotY(180.0f * RAGE);
    tmpMat = MMult(tmpMat, rotYMat);
    MV1SetRotationMatrix(modelHandle, tmpMat);
}

void Actor::UpdateMV1Pos()
{
    // 力をかけ終わったベロシティの方向にディレクションを調整.
    if (VSize(velocity) != 0)
    {
        direction = VNorm(velocity);
    }
    // ポジションを更新.
    position = VAdd(position, velocity);
    // ３Dモデルのポジション設定
    MV1SetPosition(modelHandle, position);
}
