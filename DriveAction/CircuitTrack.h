#pragma once
#include "Object.h"
#include "ArgumentConflictInfo.h"
#include "NeighborhoodInfo.h"
#include "CarNeighborhoodExamineInfo.h"
#include <string>

/// <summary>
/// コース
/// </summary>
class CircuitTrack final:
    public Object
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
    bool GetOutsideHitFlag(ConflictProccessArgumentInfo info) const;
    /// <summary>
    /// コースの壁にぶつかってるか調べる
    /// </summary>
    /// <param name="Actor">ぶつかってるか調べたいもの</param>
    /// <returns>ぶつかってたらTrue</returns>
    ConflictProccessArgumentInfo GetCourceConflictInfo(ConflictProccessArgumentInfo info) const;

    NeighborhoodInfo GetOutsideExamineInfo(CarNeighborhoodExamineInfo examineInfo) const;
    /// <summary>
    /// コースのモデルを描画
    /// </summary>
    void Draw();

private:
    ConflictProccessArgumentInfo GetSphereConflictModelInfo(int modelHandle,CarNeighborhoodExamineInfo examineInfo) const;
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
    //コースの赤白の奴
    const float gurdRadius = 2.0f;
    //コースのmodel
    int courceModelHandle;
    //コースの外側のmodel
    int outsideModelHandle;
    //コースの外側のmodelのポジション
    const VECTOR outsideModelPosition = { 0,-8,0 };
};

