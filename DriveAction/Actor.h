#pragma once
#include "Object.h"
class Actor :
    public Object
{
public:
    Actor() 
        :modelHandle(-1),
        direction({}),
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
    virtual void ConflictProcess() {};
    /// <summary>
    /// 向き所得
    /// </summary>
    /// <returns></returns>
    const VECTOR& GetDir() const
    {
        return direction;
    };
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
    //方向
    VECTOR direction;

};

