#include "DxLib.h"
#include "Effect.h"
#include "SceneBase.h"
#include "TitleScene.h"
#include "PlayScene.h"
#include "ResultScene.h"
#include "Utility.h"
#include "UserInput.h"
#include "Broom.h"
SceneBase* MakeScene(SceneType _NowSceneType);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(true);

	// DirectX11を使用するようにする。(DirectX9も可、一部機能不可)
	// Effekseerを使用するには必ず設定する。
	SetUseDirect3DVersion(DX_DIRECT3D_11);

	// 画面の解像度と色ビット深度を設定
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32);


	// １メートルに相当する値を設定する
	Set3DSoundOneMetre(16.0f);
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
	Broom* broom = new Broom;
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
	SAFE_DELETE(broom);
	SAFE_DELETE(scene);
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
