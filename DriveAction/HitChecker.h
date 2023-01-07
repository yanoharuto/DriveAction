#pragma once
struct ArgumentConflictInfo;
class Object;
/// <summary>
/// 球同士の当たり判定をやります
/// </summary>
class HitChecker
{
public:
    HitChecker();
    ~HitChecker();
    /// <summary>
    /// 当たったかどうか調べるよ
    /// </summary>
    /// <param name="objA">調べたいオブジェクトA<</param>
    /// <param name="objB">調べたいオブジェクトB</param>
    /// <returns>当たったらTrue</returns>
    bool HitCheck(Object* const objA, Object* const objB);
    /// <summary>
    /// 当たったかどうか調べるよ
    /// </summary>
    /// <param name="objA">調べたいオブジェクトA<</param>
    /// <param name="objBInfo">調べたいオブジェクトB</param>
    /// <returns>当たったらTrue</returns>
    bool HitCheck(Object* const objA, const ArgumentConflictInfo objBInfo);
    /// <summary>
    /// 当たったかどうか調べるよ
    /// </summary>
    /// <param name="objAInfo">調べたいオブジェクトA<</param>
    /// <param name="objBInfo">調べたいオブジェクトB</param>
    /// <returns>当たったらTrue</returns>
    bool HitCheck(const ArgumentConflictInfo objAInfo, const ArgumentConflictInfo objBInfo);
private:
    /// <summary>
    /// 当たったかどうか調べるときの共通処理
    /// </summary>
    /// <param name="objAInfo">調べたいオブジェクトA</param>
    /// <param name="objBInfo">調べたいオブジェクトB</param>
    /// <returns>当たったらTrue</returns>
    bool HitCheckProcess(ArgumentConflictInfo objAInfo, ArgumentConflictInfo objBInfo);
};

