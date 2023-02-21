#include "CountDown.h"
#include "DxLib.h"
#include "Utility.h"
#include "SoundPlayer.h"
#define DOWN_SCALE		8				// ガウスフィルタを掛ける画像が画面のサイズの何分の１か
CountDown::CountDown()
{
	countDownEnd = false;
	startTime = fiveTime;

	uiData.x = SCREEN_WIDTH / 2;
	uiData.y = SCREEN_HEIGHT / 7;
	highBrightGraph = MakeScreen(256, 256, FALSE);
	gaussGraph = MakeScreen(256, 256, FALSE);;
	uiData.dataHandle = LoadGraph(graphAddress.c_str());
	

	SoundPlayer::LoadSound(countDownSE);
}

CountDown::~CountDown()
{
	SAFE_DELETE(countDownUI);
	DeleteGraph(uiData.dataHandle);
	DeleteGraph(gaussGraph);
	DeleteGraph(highBrightGraph);
	DeleteGraph(lightGraph);
}

void CountDown::Update(float deltaTime)
{
	startTime -= deltaTime;
	switch (static_cast<int>(startTime))
	{
	case 3:
		if (!countStart)
		{
			SoundPlayer::Play2DSE(countDownSE);
			countStart = true;
		}
		color = lightColor1;
		count = "1";
		break;
	case 2:
		color = lightColor2;
		count = "2";
		break;
	case 1:
		color = lightColor3;
		count = "3";
		break;
	case 0:
		countDownEnd = true;
		count = "GO!!";
		break;
	default:
		count = "Count...";
		
		break;
	}
	if (countStart)
	{
		std::string string = lightGraphAddress + count + png;
		lightGraph = LoadGraph(string.c_str());
	}
}

bool CountDown::CountDownEnd()
{
	return countDownEnd;
}

void CountDown::DrawUI()
{
	//ライト本体を描画
	DrawRotaGraph(uiData.x, uiData.y, 0.5, 0, uiData.dataHandle, true, 0, 0);
	if (countStart)
	{
		//光を描画
		DrawRotaGraph(uiData.x, uiData.y, 0.5, 0, lightGraph, true, 0, 0);
		// 描画モードをバイリニアフィルタリングにする( 拡大したときにドットがぼやけるようにする )
		SetDrawMode(DX_DRAWMODE_BILINEAR);

		// 描画ブレンドモードを加算にする
		SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
		// 描画結果から高輝度部分のみを抜き出した画像を得る
		int success = GraphFilterBlt(lightGraph, highBrightGraph, DX_GRAPH_FILTER_BRIGHT_CLIP, DX_CMP_GREATER, 30, TRUE, color, 200);
		// ８分の１に縮小した画像をガウスフィルタでぼかす
		success = GraphFilterBlt(highBrightGraph, gaussGraph, DX_GRAPH_FILTER_GAUSS, 16, gaussRatio);

		// 高輝度部分を縮小してぼかした画像を画面いっぱいに２回描画する( ２回描画するのはより明るくみえるようにするため )
		DrawRotaGraph(uiData.x, uiData.y, 3, 0, gaussGraph, true, 0, 0);

		// 描画ブレンドモードをブレンド無しに戻す
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

		// 描画モードを二アレストに戻す
		SetDrawMode(DX_DRAWMODE_NEAREST);
	}
}