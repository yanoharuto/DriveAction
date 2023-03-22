#pragma once
#include <string>
#include "Actor.h"
#include "ConflictExamineResultInfo.h"
#include "HitCheckExamineObjectInfo.h"
#include "NeighborhoodInfo.h"
#include "CarNeighborhoodExamineInfo.h"
#define  COURCE_GENERATE_NUM 5
struct StageModel;
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
    CircuitTrack();
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
    /// <summary>
    /// コースのモデルを描画
    /// </summary>
    void Draw();
    void Update(VECTOR playerPos);
private:
   
    ConflictExamineResultInfo GetSphereConflictModelInfo(int modelHandle,HitCheckExamineObjectInfo examineInfo) const;
   
    //次に生成するステージの位置
    VECTOR nextGeneratePos = {};
    //最初のポジションの位置
    const VECTOR firstPos = { -150.0f,0.0f,0.0f };
    //コリジョンのYの分割数
    const int setupYDivNum = 8;
    //コースの大きさ
    const float modelScaleHandle = 0.35f;
    //はじき返す力
    const float setBouncePower = 1.0f;
    //コースの赤白の奴の大きさ
    const float gurdRadius = 3.5f;

    //コースの外側のmodelのポジション
    const VECTOR outsideModelPosition = { 0,-8,0 };
    //ステージのmodelのファイルのパス
    const std::string stageFilePass = "Stage/";
    const std::string courceFilePass = "Obstracle.mv1";
    const std::string obstracleFilePass = "Rail.mv1";
    const std::string floorFilePass = "Floor.mv1";
    //コースのモデルの数
    const int courceModelNum = 2;
    //コースのパターンの数
    const int courcePatternNum = 3;
    //次に出すmodelのエイリアス
    int random = 1;
    int obstracleModelHandle;
    int courceModelHandle;
    int floorModelHandle;
};