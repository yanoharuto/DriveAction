#pragma once
#include <string>
#include <vector>
#include "Rock.h"
#include "StageWall.h"
#include "ConflictExamineResultInfo.h"
#include "HitCheckExamineObjectInfo.h"
#include "SphereCollider.h"

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

    //コースの外側のmodelのポジション
    const float rockYPos = 20;
    //ステージのmodelのファイルのパス
    const std::string stageFilePass = "Stage/";
    
    //地面
    const std::string floorFilePass = "Floor.mv1";

    //次に出すmodelのエイリアス
    int random = 1;
    //地面
    int floorModelHandle;
    std::vector<Rock*> rocks;
    StageWall* stageWall;
};