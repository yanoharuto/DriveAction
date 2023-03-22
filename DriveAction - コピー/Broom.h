#pragma once
class Broom
{
public:
    Broom();
    ~Broom();
    void Update();
    void Draw();
private:

    int ColorScreen;	// 普通の描画結果を書き込むスクリーン
    int HighBrightScreen;	// 普通の描画結果から高輝度部分を抜き出した結果を書き込むスクリーン
    int DownScaleScreen;	// 高輝度部分を縮小した結果を書き込むスクリーン
    int GaussScreen;	// 縮小画像をガウスフィルタでぼかした結果を書き込むスクリーン
    int Angle;		// カメラの水平角度
    int StageModel;	// ステージモデル
    int GaussRatio;	// ガウスフィルタのぼかし度合い
};

