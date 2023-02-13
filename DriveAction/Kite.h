#pragma once
#include <string>
#include "Item.h"

/// <summary>
/// 爆弾を空を飛びながらばらまく
/// </summary>
class Kite :
    public ItemBase
{
public:
    Kite();
    ~Kite();
	/// <summary>
	/// 効果終了まで上昇する
	/// </summary>
	/// <param name="deltaTime"></param>
	/// <param name="carInfo"></param>
	void Update(float deltaTime,ItemArgumentCarInfo carInfo)override;
    /// <summary>
    /// 上昇するためのロケットバレルを付ける
    /// </summary>
    void Draw()override;
    /// <summary>
    /// 爆弾を発射
    /// </summary>
    /// <param name="carInfo"></param>
    void ShowEffect(ItemArgumentCarInfo carInfo)override;
private:
    void SetMatrix(int modelH, ItemArgumentCarInfo carInfo,VECTOR addPos);
    //効果時間
    const float setEffecacyTime = 4.2f;
    //爆弾をばらまく間隔
	const float setCoolTime = 0.28f;
    //空を飛ぶ力
	const float flyPower = 14.3f;
    //最大高度
	const float maxHeight = 13.0f;
    //３Dmodelのアドレス
    const std::string modelAddress = "data/model/Item/Rocket/Rocket06_Green.mv1";
    int leftRocketModelHandle;
};