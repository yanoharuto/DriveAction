#pragma once
#include "Object.h"
#include "ConflictExamineResultInfo.h"
#include "ArgumentConflictResultInfo.h"
#include "HitCheckExamineObjectInfo.h"
#include "HitChecker.h"
#include "OriginalMath.h"
/// <summary>
/// 描画するオブジェクト
/// </summary>
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
    /// <summary>
    /// 当たり判定で当たってたら渡す情報
    /// </summary>
    /// <returns></returns>
    virtual HitCheckExamineObjectInfo GetHitCheckExamineInfo()
    {
        HitCheckExamineObjectInfo objInfo;
        objInfo.SetExamineInfo(this);
        objInfo.velocity = velocity;
        return objInfo;
    };

protected:
    /// <summary>
    /// 他のオブジェクトに当たってるか調べる用の情報
    /// </summary>
    /// <returns></returns>
    ArgumentConflictResultInfo GetConflictArgumentInfo()
    {
        ArgumentConflictResultInfo resultInfo;
        resultInfo.SetObjInfo(this);
        return resultInfo;
    };
    /// <summary>
    /// 描画モデルの行列をセット
    /// </summary>
    virtual void ModelSetMatrix()
    {
        // 向きに合わせて回転.
        MV1SetRotationZYAxis(modelHandle, direction, VGet(0.0f, 1.0f, 0.0f), 0.0f);

        
        MATRIX tmpMat = MV1GetMatrix(modelHandle);
        // モデルに向いてほしい方向に回転.
        MATRIX rotYMat = MGetRotY(180.0f * RAGE);
        tmpMat = MMult(tmpMat, rotYMat);
        MV1SetRotationMatrix(modelHandle, tmpMat);
    }
    //ポジションの位置に変更する
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
    //modelのサイズ
    float modelSize = 1;
};