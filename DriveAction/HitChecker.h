#pragma once
struct ConflictExamineResultInfo;
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
    bool HitCheck(Object* const objA, const ConflictExamineResultInfo objBInfo);
    /// <summary>
    /// 当たったかどうか調べるよ
    /// </summary>
    /// <param name="objAInfo">調べたいオブジェクトA<</param>
    /// <param name="objBInfo">調べたいオブジェクトB</param>
    /// <returns>当たったらTrue</returns>
    bool HitCheck(const ConflictExamineResultInfo objAInfo, const ConflictExamineResultInfo objBInfo);
private:
    /// <summary>
    /// 当たったかどうか調べるときの共通処理
    /// </summary>
    /// <param name="objAInfo">調べたいオブジェクトA</param>
    /// <param name="objBInfo">調べたいオブジェクトB</param>
    /// <returns>当たったらTrue</returns>
    bool HitCheckProcess(ConflictExamineResultInfo objAInfo, ConflictExamineResultInfo objBInfo);
};

