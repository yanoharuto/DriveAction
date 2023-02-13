#pragma once
#include "Actor.h"
#include "DxLib.h"
/// <summary>
/// áŠQ•¨@iŠÛ‚Ì‚±j
/// </summary>
class Saw :
    public Actor
{
public:
    Saw();
    /// <summary>
    /// ˆø”‚ÌêŠ‚Éİ’u‚·‚é
    /// </summary>
    /// <param name="pos"></param>
    /// <param name="duplicateModelHandle"></param>
    Saw(VECTOR pos, int duplicateModelHandle);
    ~Saw();
    /// <summary>
    /// ‰ñ“]‚³‚¹‚é
    /// </summary>
    /// <param name="deltaTime"></param>
    void Update(const float deltaTime) override;
    /// <summary>
    /// ˆø”‚Ì•¨‘Ì‚É“–‚½‚Á‚Ä‚é‚©•Ô‚·
    /// </summary>
    /// <param name="examineObjInfo"></param>
    /// <returns></returns>
    bool HitCheckConflict(const HitCheckExamineObjectInfo examineObjInfo)override;
private:
    //‰ñ“]—Ê
    const float addRotate = 22.0f;
    //•
    const float setRadius = 23.0f;
    //‚Í‚¶‚«•Ô‚·—Í
    const float setBouncePower = 4.0f;
    //Œú‚İ
    const float thickness = 5.0f;
    //‰ñ“]
    float rotate = 0;
};