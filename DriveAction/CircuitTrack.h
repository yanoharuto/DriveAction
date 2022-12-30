#pragma once
#include "Stage.h"
class Player;
/// <summary>
/// コース
/// </summary>
class CircuitTrack final:
    public Stage
{
public:
    /// <summary>
    /// 初期化
    /// </summary>
    /// <returns></returns>
    CircuitTrack(Player* player);
    
    ///modelをデリート
    ~CircuitTrack();
    /// <summary>
    /// コースの外側に当たってるか調べる
    /// </summary>
    /// <param name="actor">外側にいるか調べたいもの</param>
    /// <returns>コースの外側にいるならTrue</returns>
    bool GetOutsideHitFlag(Actor* actor);
    /// <summary>
    /// コースの壁にぶつかってるか調べる
    /// </summary>
    /// <param name="Actor">ぶつかってるか調べたいもの</param>
    /// <returns>ぶつかってたらTrue</returns>
    bool GetGurdHitFlag(Actor* Actor);
    /// <summary>
    /// コースのモデルを描画
    /// </summary>
    void Draw();
private:
    //コリジョンのYの分割数
    const int setupYDivNum = 8;
    //コースの大きさ
    const float courceModeScaleValue = 0.15f;
    //コースの外側の大きさ
    const float outsideModelScaleValue = 0.15f;
    //コースの位置探索に使う線分の始点
    const float sY = 0;
    //コースの位置探索に使う線分の終点
    const float eY = -11;
    //コースのmodel
    int courceModelHandle;
    //コースの外側のmodel
    int outsideModelHandle;
    //コースの外側のmodelのポジション
    VECTOR outsideModelPosition = { 0,-8,0 };
};

