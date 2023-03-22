#pragma once
#include <string>
#include "ConflictExamineResultInfo.h"
#include "HitCheckExamineObjectInfo.h"
#include "MeshCollider.h"

#define  COURCE_GENERATE_NUM 5
struct StageModel;
/// <summary>
/// コース
/// </summary>
class CircuitTrack final
{
public:
    /// <summary>
    /// 初期化
    /// </summary>
    CircuitTrack();
    ///modelをデリート
    ~CircuitTrack();
    /// <summary>
    /// コースのモデルを描画
    /// </summary>
    void Draw();
private:
    ConflictExamineResultInfo resultInfo = { false,ObjectTag::stage,{},{},0.0f,15.0f };
    //コースの大きさ
    const float modelScaleHandle = 0.35f;
    
    //障害物の幅
    const float setRadius = 3.5f;

    //コースの外側のmodelのポジション
    const VECTOR outsideModelPosition = { 0,-200,0 };
    //ステージのmodelのファイルのパス
    const std::string stageFilePass = "Stage/";
    //レール
    const std::string courceFilePass = "Rail.mv1";
    //障害物
    const std::string obstracleFilePass = "Obstracle.mv1";
    //地面
    const std::string floorFilePass = "Floor.mv1";
    //コースのモデルの数
    const int courceModelNum = 2;
    //コースのパターンの数
    const int courcePatternNum = 3;
    //次に出すmodelのエイリアス
    int random = 1;
    
    //障害物モデルハンドル
    int obstracleModelHandle;
    //コース
    int courceModelHandle;
    //地面
    int floorModelHandle;
    MeshCollider* obstracleCollider;
    MeshCollider* courceCollider;
    MeshCollider* floorCollider;
};