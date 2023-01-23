#include "HitChecker.h"
#include "Object.h"
#include "ConflictExamineResultInfo.h"
#include "DxLib.h"
HitChecker::HitChecker()
{
}

HitChecker::~HitChecker()
{
}
/// <summary>
/// 当たったかどうか調べるよ
/// </summary>
/// <param name="objA">調べたいオブジェクトA</param>
/// <param name="objB">調べたいオブジェクトB</param>
/// <returns>当たったらTrue</returns>
bool HitChecker::HitCheck(Object* const objA, Object* const objB)
{
    ConflictExamineResultInfo aInfo;
    aInfo.SetObjInfo(false, objA);
    ConflictExamineResultInfo bInfo;
    bInfo.SetObjInfo(false,objB);
    return HitCheckProcess(aInfo, bInfo);
}
/// <summary>
/// 当たったかどうか調べるよ
/// </summary>
/// <param name="objA">調べたいオブジェクトA</param>
/// <param name="objBInfo">調べたいオブジェクトB</param>
/// <returns>当たったらTrue</returns>
bool HitChecker::HitCheck(Object* const objA, const ConflictExamineResultInfo objBInfo)
{
    ConflictExamineResultInfo aInfo;
    aInfo.SetObjInfo(false,objA);
    return HitCheckProcess(aInfo, objBInfo);
}
/// <summary>
/// 当たったかどうか調べるよ
/// </summary>
/// <param name="objAInfo">調べたいオブジェクトA</param>
/// <param name="objBInfo">調べたいオブジェクトB</param>
/// <returns>当たったらTrue</returns>
bool HitChecker::HitCheck(const ConflictExamineResultInfo objAInfo, const ConflictExamineResultInfo objBInfo)
{
    return HitCheckProcess(objAInfo, objBInfo);
}
/// <summary>
/// 当たったかどうか調べるときの共通処理
/// </summary>
/// <param name="objAInfo">調べたいオブジェクトA</param>
/// <param name="objBInfo">調べたいオブジェクトB</param>
/// <returns>当たったらTrue</returns>
bool HitChecker::HitCheckProcess(ConflictExamineResultInfo objAInfo, ConflictExamineResultInfo objBInfo)
{
    //引数同士の距離
    VECTOR distance = VSub(objAInfo.pos, objBInfo.pos);
    distance.y = 0;
    //引数同士の当たり判定の合計
    float range = objAInfo.radius + objBInfo.radius;
    if (range > VSize(distance))
    {
        return true;
    }
    return false;
}