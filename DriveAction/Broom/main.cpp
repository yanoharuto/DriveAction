// ブルーム効果基本
#include "DxLib.h"

#define SCREEN_W		640				// 画面の横幅
#define SCREEN_H		480				// 画面の縦幅
#define DOWN_SCALE		8				// ガウスフィルタを掛ける画像が画面のサイズの何分の１か
#define DOWN_SCALE_SCREEN_W	( SCREEN_W / DOWN_SCALE )	// ガウスフィルタを掛ける画像の横幅
#define DOWN_SCALE_SCREEN_H	( SCREEN_H / DOWN_SCALE )	// ガウスフィルタを掛ける画像の縦幅

int ColorScreen;	// 普通の描画結果を書き込むスクリーン
int HighBrightScreen;	// 普通の描画結果から高輝度部分を抜き出した結果を書き込むスクリーン
int DownScaleScreen;	// 高輝度部分を縮小した結果を書き込むスクリーン
int GaussScreen;	// 縮小画像をガウスフィルタでぼかした結果を書き込むスクリーン

// WinMain関数
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	int Angle;		// カメラの水平角度
	int StageModel;	// ステージモデル
	int GaussRatio;	// ガウスフィルタのぼかし度合い

	// ウインドウモードで起動
	ChangeWindowMode(TRUE);

	// 画面の解像度と色ビット深度を設定
	SetGraphMode(SCREEN_W, SCREEN_H, 32);

	// ＤＸライブラリの初期化
	if (DxLib_Init() < 0)
		return -1;

	// ステージモデルの読み込み
	StageModel = MV1LoadModel("BloomTestStage.mqo");

	// 通常の描画結果を書き込むスクリーンと、フィルターの処理結果を書き込むスクリーンの作成
	ColorScreen = MakeScreen(SCREEN_W, SCREEN_H, FALSE);
	HighBrightScreen = MakeScreen(SCREEN_W, SCREEN_H, FALSE);
	DownScaleScreen = MakeScreen(DOWN_SCALE_SCREEN_W, DOWN_SCALE_SCREEN_H, FALSE);
	GaussScreen = MakeScreen(DOWN_SCALE_SCREEN_W, DOWN_SCALE_SCREEN_H, FALSE);

	// ClearDrawScreen 時に画面に塗りつぶす色をセット( 真っ白 )
	SetBackgroundColor(255, 255, 255);

	// カメラの角度とガウスフィルタのぼかし度合いを初期化
	Angle = 0;
	GaussRatio = 900;

	// メインループ(何かキーが押されたらループを抜ける)
	while (ProcessMessage() == 0)
	{
		// 左右キーが押されたらカメラを回転する
		if (CheckHitKey(KEY_INPUT_LEFT))
		{
			Angle -= 3;
			if (Angle < 0)
			{
				Angle += 360;
			}
		}
		if (CheckHitKey(KEY_INPUT_RIGHT))
		{
			Angle += 3;
			if (Angle > 360)
			{
				Angle -= 360;
			}
		}

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


		// 通常の描画結果を書き込むスクリーンを描画対象にする
		SetDrawScreen(ColorScreen);

		// 画面をクリア
		ClearDrawScreen();


		// カメラの位置と向きを設定
		SetCameraPositionAndAngle(VGet(0.0f, 120.0f, 0.0f), 0.0f, Angle / 180.0f * 3.14159f, 0.0f);

		// ステージモデルの描画
		MV1DrawModel(StageModel);


		// 描画結果から高輝度部分のみを抜き出した画像を得る
		GraphFilterBlt(ColorScreen, HighBrightScreen, DX_GRAPH_FILTER_BRIGHT_CLIP, DX_CMP_LESS, 230, TRUE, GetColor(0, 0, 0), 255);

		// 高輝度部分を８分の１に縮小した画像を得る
		GraphFilterBlt(HighBrightScreen, DownScaleScreen, DX_GRAPH_FILTER_DOWN_SCALE, DOWN_SCALE);

		// ８分の１に縮小した画像をガウスフィルタでぼかす
		GraphFilterBlt(DownScaleScreen, GaussScreen, DX_GRAPH_FILTER_GAUSS, 16, GaussRatio);


		// 描画対象を裏画面にする
		SetDrawScreen(DX_SCREEN_BACK);


		// 通常の描画結果を描画する
		DrawGraph(0, 0, ColorScreen, FALSE);


		// 描画モードをバイリニアフィルタリングにする( 拡大したときにドットがぼやけるようにする )
		SetDrawMode(DX_DRAWMODE_BILINEAR);

		// 描画ブレンドモードを加算にする
		SetDrawBlendMode(DX_BLENDMODE_ADD, 255);

		// 高輝度部分を縮小してぼかした画像を画面いっぱいに２回描画する( ２回描画するのはより明るくみえるようにするため )
		DrawExtendGraph(0, 0, SCREEN_W, SCREEN_H, GaussScreen, FALSE);
		DrawExtendGraph(0, 0, SCREEN_W, SCREEN_H, GaussScreen, FALSE);

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


		// 裏画面の内容を表画面に反映
		ScreenFlip();
	}

	// ＤＸライブラリの後始末
	DxLib_End();

	// ソフトの終了
	return 0;
}