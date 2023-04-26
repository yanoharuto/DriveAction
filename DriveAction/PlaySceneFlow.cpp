#include "PlaySceneFlow.h"
#include "PlayerRelatedInfo.h"
#include "Utility.h"
#include "AssetManager.h"
#include "CoinManager.h"
#include "ConflictManager.h"
#include "DamageObjectGenerator.h"
#include "EffectManager.h"
#include "FlyShipManager.h"
#include "FiringItemManager.h"
#include "PostGoalStaging.h"
#include "PlayerRelatedUI.h"
#include "RacePrevProcess.h"
#include "RaceScreen.h"
#include "EffekseerForDXLib.h"
#include "CourceDataLoader.h"
#include "CountDown.h"
#include "RaceCamera.h"
#include "RacerManager.h"
#include "ResultScore.h"
#include "Rule.h"
#include "StageManager.h"
#include "SoundPlayer.h"
#include "ShadowMap.h"
#include "UIManager.h"
PlaySceeneFlow::PlaySceeneFlow()
{
	uiManager = new UIManager();
	conflictManager = new ConflictManager();
	courceDataLoader = new CourceDataLoader();
	nowProgress = PlaySceeneProgress::start;
	stageManager = new StageManager();
	camera = new RaceCamera();
	gameLimitTimer = new Timer(MAX_GAME_TIME);
	postGoalStaging = nullptr;
	modelManager = new AssetManager();
	firingManager = new FiringItemManager();
	racerManager = new RacerManager(CPU_RACER_NUM);
	coinManager = new CoinManager();
	playerUI = new PlayerRelatedUI(gameLimitTimer,coinManager->GetCoinFirstNum());
	effectManager = new EffectManager();
	flyShipManager = new FlyShipManager(); 
	shadowMap = new ShadowMap();
	stageManager = new StageManager();
	racePrevProccess = new RacePrevProcess();
	countDown = new CountDown(gameLimitTimer);
	screen = new RaceScreen();
	
	SoundPlayer::LoadSound(BGMPass);
	SoundPlayer::SetSoundVolume(BGMBolume, BGMPass);

	PlayerRelatedInfo playerRelatedInfo = PlayerInformationCenter::GetPlayerRelatedInfo(0);
	ObjInfo playerPosAndDir = playerRelatedInfo.objInfo;
	//カメラの処理
	camera->Update(playerPosAndDir);
#ifdef _DEBUG
#endif
}

PlaySceeneFlow::~PlaySceeneFlow()
{
	SAFE_DELETE(racerManager)
	SAFE_DELETE(stageManager);
	SAFE_DELETE(camera);
	SAFE_DELETE(courceDataLoader);
	SAFE_DELETE(postGoalStaging);
	SAFE_DELETE(playerUI);
	SAFE_DELETE(score);
	SAFE_DELETE(modelManager);
	SAFE_DELETE(firingManager);
	SAFE_DELETE(effectManager);
	SAFE_DELETE(flyShipManager);
	SAFE_DELETE(conflictManager);
	SAFE_DELETE(shadowMap);
	SAFE_DELETE(racePrevProccess);
	SAFE_DELETE(coinManager);
	SAFE_DELETE(gameLimitTimer);
	SAFE_DELETE(countDown);
	SAFE_DELETE(screen);
	SAFE_DELETE(uiManager);
#ifdef _DEBUG
#endif

}

void PlaySceeneFlow::Update()
{
	
	int key = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	PlayerRelatedInfo playerRelatedInfo = PlayerInformationCenter::GetPlayerRelatedInfo(0);
	ObjInfo playerPosAndDir = playerRelatedInfo.objInfo;
	stageManager->Update();
	//コインの更新
	coinManager->Update(playerPosAndDir);
	switch (nowProgress)
	{
		//スタート処理
	case PlaySceeneProgress::start:
		racePrevProccess->Update();
		racerManager->UpDown();
		if (racePrevProccess->IsProccesEnd())
		{
			nowProgress = PlaySceeneProgress::race;
			SoundPlayer::Play2DSE(BGMPass);
		}
		break;
		//レース
	case PlaySceeneProgress::race:
		gameLimitTimer->Update();
		//レーサーの処理
		racerManager->RacerUpdate();
		flyShipManager->Update(racerManager->GetPlayerRelatedInfo());
		//発射物の更新
		firingManager->Update();
		//当たり判定処理
		conflictManager->Update();
		//プレイヤーUI
		playerUI->Update(playerRelatedInfo,coinManager->GetCoinPosList());
		//残り三秒になったらカウントダウンしてくれる
		countDown->Update();
		//レース終了
		if (gameLimitTimer->IsOverLimitTime() || coinManager->GetCoinNowNum() == 0)
		{
			nowProgress = PlaySceeneProgress::playerGoal;
			score = new ResultScore(gameLimitTimer, playerRelatedInfo);
			//ゴール後の処理をお願い
			postGoalStaging = new PostGoalStaging();
		}
		break;
	case PlaySceeneProgress::playerGoal:

		if (postGoalStaging->Update())
		{
			nowProgress = PlaySceeneProgress::end;
		}
		break;
	case PlaySceeneProgress::end:
		nextSceneType = SceneType::TITLE;
		isEndProccess = true;
		break;
	default:
		nowProgress = PlaySceeneProgress::end;
		break;
	}
	//カメラの処理
	camera->Update(playerPosAndDir);
	//シャドウマップの更新
	shadowMap->SetShadowMapErea(racerManager->GetPlayerCarPosDir());
	// DXライブラリのカメラとEffekseerのカメラを同期する。
	Effekseer_Sync3DSetting();
	// Effekseerにより再生中のエフェクトを更新する。
	UpdateEffekseer3D();
#ifdef _DEBUG
#endif
}

void PlaySceeneFlow::Draw()
{	
	shadowMap->SetUP();
	ManagerDraw();
	shadowMap->DrawEnd();
	ManagerDraw();
	shadowMap->Use();
	switch (nowProgress)
	{
	case PlaySceeneProgress::start:
		racePrevProccess->Draw();
	case PlaySceeneProgress::race:
		// Effekseerにより再生中のエフェクトを描画する。
		DrawEffekseer3D();
		screen->SetUp();
		playerUI->Draw();
		countDown->DrawUI();
		break;
	case PlaySceeneProgress::playerGoal:
	case PlaySceeneProgress::end:
		postGoalStaging->Draw();
		break;
	}
#ifdef DEBUG
	conflictManager->DrawCollisionSphere();
#endif // DEBUG

}

void PlaySceeneFlow::ManagerDraw()
{
	if (nowProgress != PlaySceeneProgress::playerGoal)
	{
		firingManager->Draw();
		racerManager->Draw();
		flyShipManager->Draw();
		stageManager->Draw();
		coinManager->Draw();
	}
}