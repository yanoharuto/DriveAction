#pragma once
#include "Object.h"
#include "ConflictExamineResultInfo.h"
/// <summary>
/// 動くものは大体これ
/// </summary>
class Actor :
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
    virtual void Draw() {};
    /// <summary>
    /// 衝突処理
    /// </summary>
    /// <param name="tag">衝突した物体</param>
    virtual void ConflictProcess(float deltaTime, const ConflictExamineResultInfo conflictInfo) {};

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