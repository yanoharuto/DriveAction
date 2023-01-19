#include "DxLib.h"
#include "Effect.h"
#include "SceneBase.h"
#include "TitleScene.h"
#include "PlayScene.h"
#include "ResultScene.h"
#include "Utility.h"
#include "UserInput.h"

SceneBase* MakeScene(SceneType _NowSceneType);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

	//描画先を裏画面に変更する。
	SetDrawScreen(DX_SCREEN_BACK);

	// DirectX11を使用するようにする。(DirectX9も可、一部機能不可)
	// Effekseerを使用するには必ず設定する。
	SetUseDirect3DVersion(DX_DIRECT3D_11);
	int width = SCREEN_WIDTH;
	int height = SCREEN_HEIGHT;
	// 画面モードのセット.
	SetGraphMode(width, height, 16);
	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}
	//Effekseerを初期化する
	if (Effect_Initialize() == -1) 
	{
		DxLib_End();
		return -1;
	}

	//ChangeWindowMode(TRUE);
	//ひとつ前のシーン
	SceneType prevSceneType = SceneType::TITLE;
	//今のシーン
	SceneType nowSceneType = SceneType::TITLE;
	//シーンを生成
	SceneBase* scene = new TitleScene;

	UserInput* userInput = new UserInput;

	//ゲームループ エスケープキーを押したら終了
	while (ProcessMessage() == 0 && !CheckHitKey(KEY_INPUT_ESCAPE))
	{

#ifdef _DEBUG
		clsDx(); // printfDx の結果をリセットするための関数.
#endif	// ここでDEBUG用の処理を終了.
		//更新
	
		nowSceneType = scene->Update();
		Effect_Update();
		userInput->Update();
		ClearDrawScreen();//画面を初期化する
		scene->Draw();//描画
		Effect_Draw();
		ScreenFlip();//裏画面の内容を表画面に反映させる

		//Updateで次のシーンに更新したなら
		if (nowSceneType != prevSceneType)
		{
			SAFE_DELETE(scene);//シーンの開放
			//新しいシーンの作成
			scene = MakeScene(nowSceneType);
		}
		//直前のシーンを記録
		prevSceneType = nowSceneType;
	}

	Effect_Finalize();

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}
/// <summary>
/// 新しく使うシーンを確保
/// </summary>
/// <param name="_NowSceneType"></param>
/// <returns></returns>
SceneBase* MakeScene(SceneType _NowSceneType)
{
	SceneBase* retScene = nullptr;
	switch (_NowSceneType)
	{
	case SceneType::TITLE:
		retScene = new TitleScene;
		break;
	case SceneType::PLAY:
		retScene = new PlayScene;
		break;
	case SceneType::RESULT:
		retScene = new ResultScene;
		break;
	default:
		break;
	}
	return retScene;
}
