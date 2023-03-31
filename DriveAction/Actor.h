#pragma once
#include "Object.h"
#include "ConflictExamineResultInfo.h"
#include "ArgumentConflictResultInfo.h"
#include "HitCheckExamineObjectInfo.h"
#include "HitChecker.h"
#include "OriginalMath.h"
class Actor abstract:
    public Object
{
public:
    Actor() 
        :modelHandle(-1),
        velocity({})
    {
    };
    virtual ~Actor()
    {
    };
    /// <summary>
    /// 更新
    /// </summary>
    virtual void Update() {};
    /// <summary>
    /// 描画
    /// </summary>
    virtual void Draw()
    {
        if (modelHandle != - 1)
        {
            ModelSetMatrix();
            UpdateMV1Pos();
            MV1DrawModel(modelHandle);
        }
    }
    
    /// <summary>
    /// 衝突処理
    /// </summary>
    virtual void ConflictProccess(const ConflictExamineResultInfo conflictInfo) {};
    /// <summary>
    /// 速度所得
    // </summary>
    /// <returns></returns>
    VECTOR GetVelocity()
    {
        return velocity;
    }
    virtual HitCheckExamineObjectInfo GetHitCheckExamineInfo()
    {
        HitCheckExamineObjectInfo objInfo;
        objInfo.SetExamineInfo(this);
        objInfo.velocity = velocity;
        return objInfo;
    };
protected:
    
    ArgumentConflictResultInfo GetConflictArgumentInfo()
    {
        ArgumentConflictResultInfo resultInfo;
        resultInfo.SetObjInfo(this);
        return resultInfo;
    };
    virtual void ModelSetMatrix()
    {
        // 向きに合わせて回転.
        MV1SetRotationZYAxis(modelHandle, direction, VGet(0.0f, 1.0f, 0.0f), 0.0f);

        // モデルに向いてほしい方向に回転.
        MATRIX tmpMat = MV1GetMatrix(modelHandle);
        MATRIX rotYMat = MGetRotY(180.0f * RAGE);
        tmpMat = MMult(tmpMat, rotYMat);
        MV1SetRotationMatrix(modelHandle, tmpMat);
    }
    virtual void UpdateMV1Pos()
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
    //描画モデル
    int modelHandle;
    //速度
    VECTOR velocity;
};