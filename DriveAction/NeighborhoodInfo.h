#pragma once
/// <summary>
/// 周辺の状況
/// </summary>
enum class NeighborhoodSituation
{
    cource,//普通に走れるコース
    outside,//コースの外側
    player,//プレイヤーがいる
    obstacle//障害物がある
};
/// <summary>
/// 周辺情報　
/// </summary>
struct NeighborhoodInfo
{
    //各方向に何があるか教える
    NeighborhoodSituation diagonallyForwardRight, forward, diagonallyForwardLeft;
}; 
