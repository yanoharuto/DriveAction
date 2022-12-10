#include "DxLib.h"
#include "SceneBase.h"
#include "TitleScene.h"
#include "PlayScene.h"
#include "ResultScene.h"
#include "Utility.h"
#include "UserInput.h"

SceneBase* MakeScene(SceneType _NowSceneType);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}
	// 画面モードのセット.
	SetGraphMode(640, 480, 16);
	ChangeWindowMode(TRUE);

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
		//更新
		nowSceneType = scene->Update();
		userInput->Update();

#ifdef _DEBUG
		clsDx(); // printfDx の結果をリセットするための関数.

#endif	// ここでDEBUG用の処理を終了.

		ClearDrawScreen();//画面を初期化する
		scene->Draw();//描画
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
