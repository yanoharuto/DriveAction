#include "Broom.h"
#include "Utility.h"
#include "DxLib.h"
#define DOWN_SCALE		8				// ガウスフィルタを掛ける画像が画面のサイズの何分の１か
#define DOWN_SCALE_SCREEN_W	( SCREEN_WIDTH / DOWN_SCALE )	// ガウスフィルタを掛ける画像の横幅
#define DOWN_SCALE_SCREEN_H	( SCREEN_HEIGHT / DOWN_SCALE )	// ガウスフィルタを掛ける画像の縦幅

Broom::Broom()
{
	// 通常の描画結果を書き込むスクリーンと、フィルターの処理結果を書き込むスクリーンの作成
	ColorScreen = MakeScreen(SCREEN_WIDTH, SCREEN_HEIGHT, FALSE);
	HighBrightScreen = MakeScreen(SCREEN_WIDTH, SCREEN_HEIGHT, FALSE);
	DownScaleScreen = MakeScreen(DOWN_SCALE_SCREEN_W, DOWN_SCALE_SCREEN_H, FALSE);
	GaussScreen = MakeScreen(DOWN_SCALE_SCREEN_W, DOWN_SCALE_SCREEN_H, FALSE);
	// カメラの角度とガウスフィルタのぼかし度合いを初期化
	Angle = 0;
	GaussRatio = 900;
}

Broom::~Broom()
{
}

void Broom::Update()
{
	// 上下キーが押されたらガウスフィルタのぼかし度合いを変更する
	if (CheckHitKey(KEY_INPUT_UP))
	{
		GaussRatio++;
	}
	if (CheckHitKey(KEY_INPUT_DOWN))
	{
		if (GaussRatio > 0)
			GaussRatio--;
	}
	// カメラの位置と向きを設定
	SetCameraPositionAndAngle(VGet(0.0f, 120.0f, 0.0f), 0.0f, Angle / 180.0f * 3.14159f, 0.0f);
	// 通常の描画結果を書き込むスクリーンを描画対象にする
	SetDrawScreen(ColorScreen);
}

void Broom::Draw()
{
	// 描画結果から高輝度部分のみを抜き出した画像を得る
	int success = GraphFilterBlt(ColorScreen, HighBrightScreen, DX_GRAPH_FILTER_BRIGHT_CLIP, DX_CMP_LESS, 230, TRUE, GetColor(0, 0, 0), 255);

	// 高輝度部分を８分の１に縮小した画像を得る
	success = GraphFilterBlt(HighBrightScreen, DownScaleScreen, DX_GRAPH_FILTER_DOWN_SCALE, DOWN_SCALE);

	// ８分の１に縮小した画像をガウスフィルタでぼかす
	success = GraphFilterBlt(DownScaleScreen, GaussScreen, DX_GRAPH_FILTER_GAUSS, 16, GaussRatio);

	// 通常の描画結果を描画する
	DrawGraph(0, 0, ColorScreen, FALSE);

	// 描画モードをバイリニアフィルタリングにする( 拡大したときにドットがぼやけるようにする )
	SetDrawMode(DX_DRAWMODE_BILINEAR);

	// 描画ブレンドモードを加算にする
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);

	// 高輝度部分を縮小してぼかした画像を画面いっぱいに２回描画する( ２回描画するのはより明るくみえるようにするため )
	DrawExtendGraph(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, GaussScreen, FALSE);
	DrawExtendGraph(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, GaussScreen, FALSE);

	// 描画ブレンドモードをブレンド無しに戻す
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	// 描画モードを二アレストに戻す
	SetDrawMode(DX_DRAWMODE_NEAREST);

	// フィルター処理の途中経過が分かるように画面下部に縮小して描画する
	DrawExtendGraph(180 * 0 + 24, 320, 180 * 0 + 24 + 160, 120 + 320, HighBrightScreen, FALSE);
	DrawExtendGraph(180 * 1 + 24, 320, 180 * 1 + 24 + 160, 120 + 320, DownScaleScreen, FALSE);
	DrawExtendGraph(180 * 2 + 24, 320, 180 * 2 + 24 + 160, 120 + 320, GaussScreen, FALSE);

	// 現在のガウスフィルタのぼかし度合いを描画する
	DrawFormatString(0, 0, GetColor(255, 255, 255), "Gauss:%d", GaussRatio);
}
