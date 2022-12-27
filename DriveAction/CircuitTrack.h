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
    /// ステージのどのmaterialの上にいるか調べる
    /// </summary>
    /// <param name="object"></param>
    void ConflictProcess(Actor* actor)override;
    /// <summary>
    /// コースのモデルを描画
    /// </summary>
    void Draw();

private:
    float const scaleValue = 0.15f;
    int modelHandle;
    int materialNum;
    float sY = 0.5;
    float eY = -1.2;
};

