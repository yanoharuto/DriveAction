#pragma once
#include "PlayerRelatedInfo.h"
#include "Timer.h"
#define SCORE_KIND_NUM 4

/// <summary>
/// 最終的なスコアの保存役
/// </summary>
class ResultScore
{
public:
    enum ScoreKind
    {
        time = 0,
        hit = 1,
        collect = 2,
        total = 3
    };
    /// <summary>
    /// 最終的なスコアの保存
    /// </summary>
    ResultScore(Timer* timer,PlayerRelatedInfo playerInfo);
    ~ResultScore() {};
    /// <summary>
    /// スコアの所得
    /// </summary>
    /// <returns></returns>
    static int GetScore(ScoreKind);
    static int GetScore(int kindNum);
    /// <summary>
    /// コインを取ったスコア
    /// </summary>
    /// <returns></returns>
    static int GetCollectBonus();
    /// <summary>
    /// 当たった回数分ヘルスコア
    /// </summary>
    /// <returns></returns>
    static int GetHitBunus();
    /// <summary>
    /// 残り時間のスコア
    /// </summary>
    /// <returns></returns>
    static int GetTimeBunus();
private:
    //コインのスコア
    static int coinScore;
    //ダメージを受けた回数減るスコア
    static int hitScore;
    //残り時間スコア
    static int timeScore;
    //ダメージ判定のあるオブジェクトに触れたらスコア減少
    const int damageObjHitDec = 30;
    //残り時間のボーナス
    const int timeBonus = 10;
    //一度も当たらなかった場合のスコア
    const int noHitScore = 500;
    //コインはボーナス
    const int coinBonus = 500;
};

