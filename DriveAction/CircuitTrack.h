#pragma once
#include <string>
#include "Actor.h"
#include "ConflictExamineResultInfo.h"
#include "HitCheckExamineObjectInfo.h"
#include "NeighborhoodInfo.h"
#include "CarNeighborhoodExamineInfo.h"
/// <summary>
/// コース
/// </summary>
class CircuitTrack final:
    public Actor
{
public:
    /// <summary>
    /// 初期化
    /// </summary>
    /// <param name="courceModelAdress"></param>
    /// <param name="outsideModelAdress"></param>
    /// <returns></returns>
    CircuitTrack(std::string courceModelAdress,std::string outsideModelAdress);
    CircuitTrack() {
        courceModelHandle = -1;
        outsideModelHandle = -1;
    };
    ///modelをデリート
    ~CircuitTrack();
    /// <summary>
    /// コースの外側に当たってるか調べる
    /// </summary>
    /// <param name="actor">外側にいるか調べたいもの</param>
    /// <returns>コースの外側にいるならTrue</returns>
    bool GetOutsideHitFlag(HitCheckExamineObjectInfo info) const;
    bool HitCheckConflict(const HitCheckExamineObjectInfo examineObjInfo);
    /// <summary>
    /// コースの壁にぶつかってるか調べる
    /// </summary>
    /// <param name="Actor">ぶつかってるか調べたいもの</param>
    /// <returns>ぶつかってたらTrue</returns>
    ConflictExamineResultInfo GetCourceConflictInfo(HitCheckExamineObjectInfo info) const;
    NeighborhoodInfo GetOutsideExamineInfo(HitCheckExamineObjectInfo examineInfo) const;
    /// <summary>
    /// コースのモデルを描画
    /// </summary>
    void Draw();

private:
    ConflictExamineResultInfo GetSphereConflictModelInfo(int modelHandle,HitCheckExamineObjectInfo examineInfo) const;
    //コリジョンのYの分割数
    const int setupYDivNum = 8;
    //コースの大きさ
    const float courceModelScaleValue = 0.15f;
    //コースの外側の大きさ
    const float outsideModelScaleValue = 0.15f;
    //コースの位置探索に使う線分の始点
    const float sY = 0;
    //コースの位置探索に使う線分の終点
    const float eY = -11;
    //はじき返す力
    const float setBouncePower = 1.0f;
    //コースの赤白の奴の大きさ
    const float gurdRadius = 3.5f;
    //コースのmodel
    int courceModelHandle;
    //コースの外側のmodel
    int outsideModelHandle;
    //コースの外側のmodelのポジション
    const VECTOR outsideModelPosition = { 0,-8,0 };

};

