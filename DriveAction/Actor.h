#pragma once
#include "Object.h"
#include "ConflictExamineResultInfo.h"
#include "HitCheckExamineObjectInfo.h"
#include "HitChecker.h"

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
    virtual void Update(const float deltaTime) {};
    /// <summary>
    /// 描画
    /// </summary>
    virtual void Draw()
    {
        MV1DrawModel(modelHandle);
    }
    /// <summary>
    /// 引数のオブジェクトとぶつかったか調べる
    /// </summary>
    /// <param name="deltaTime"></param>
    /// <param name="conflictInfo"></param>
    virtual bool HitCheckConflict (const HitCheckExamineObjectInfo examineObjInfo) 
    {
        return  HitChecker::HitCheck(this, examineObjInfo);
    };
    /// <summary>
    /// 衝突処理
    /// </summary>
    virtual void ConflictProccess() {};
    virtual void ConflictProccess(const ConflictExamineResultInfo conflictInfo) {};
    virtual void ConflictProccess(float deltaTime, const ConflictExamineResultInfo conflictInfo) {};
    /// <summary>
    /// 速度所得
    // </summary>
    /// <returns></returns>
    const VECTOR& GetVelocity() const
    {
        return velocity;
    }

protected:
    //描画モデル
    int modelHandle;
    //速度
    VECTOR velocity;
};