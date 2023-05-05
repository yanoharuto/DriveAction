#include "PlaySceneFlow.h"
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

#include "RaceCamera.h"
#include "RacerManager.h"
#include "ResultScore.h"
#include "Rule.h"
#include "StageManager.h"
#include "SoundPlayer.h"
#include "ShadowMap.h"
#include "UIManager.h"
/// <summary>
/// ゲームしているときの流れ
/// </summary>
PlaySceneFlow::PlaySceneFlow()
{
	uiManager = new UIManager();	
	effectManager = new EffectManager();
	conflictManager = new ConflictManager();

	racerManager = new RacerManager(1);
	courceDataLoader = new CourceDataLoader();
	stageManager = new StageManager();
	camera = new RaceCamera(racerManager);
	nowProgress = PlaySceeneProgress::start;

	gameLimitTimer = new Timer(MAX_GAME_TIME);
	postGoalStaging = nullptr;
	score = nullptr;
	modelManager = new AssetManager();
	firingManager = new FiringItemManager();
	
	coinManager = new CoinManager();
	flyShipManager = new FlyShipManager(racerManager); 
	shadowMap = new ShadowMap(racerManager);
	stageManager = new StageManager();
	racePrevProccess = new RacePrevProcess();
	screen = new RaceScreen();
	playerUI = new PlayerRelatedUI(gameLimitTimer,coinManager->GetCoinFirstNum(),racerManager);

	SoundPlayer::LoadSound(BGMPass);
	SoundPlayer::SetSoundVolume(BGMBolume, BGMPass);
	UpdateFunc[PlaySceneFlow::start] = &PlaySceneFlow::StartUpdate;
	UpdateFunc[PlaySceneFlow::game] = &PlaySceneFlow::GameUpdate;
	UpdateFunc[PlaySceneFlow::playerGoal] = &PlaySceneFlow::PlayerGoalUpdate;
	UpdateFunc[PlaySceneFlow::end] = &PlaySceneFlow::EndUpdate;
	//カメラの処理
	camera->Update();
#ifdef _DEBUG
#endif
}

PlaySceneFlow::~PlaySceneFlow()
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
	
	SAFE_DELETE(screen);
	SAFE_DELETE(uiManager);
#ifdef _DEBUG
#endif

}

void PlaySceneFlow::Update()
{
	(this->*UpdateFunc[nowProgress])();
	// DXライブラリのカメラとEffekseerのカメラを同期する。
	Effekseer_Sync3DSetting();
	// Effekseerにより再生中のエフェクトを更新する。
	UpdateEffekseer3D();
#ifdef _DEBUG
#endif
}

void PlaySceneFlow::Draw()
{	
	shadowMap->SetUP();
	DrawManagers();
	shadowMap->DrawEnd();
	DrawManagers();
	shadowMap->Use();
	switch (nowProgress)
	{
	case PlaySceeneProgress::start:
		racePrevProccess->Draw();
	case PlaySceeneProgress::game:
		// Effekseerにより再生中のエフェクトを描画する。
		DrawEffekseer3D();
		screen->ScreenUpdate();
		playerUI->Draw();

		conflictManager->DrawCollisionSphere();
		break;
	case PlaySceeneProgress::playerGoal:
	case PlaySceeneProgress::end:
		postGoalStaging->Draw();
		break;
	}
#ifdef DEBUG

#endif // DEBUG

}

void PlaySceneFlow::DrawManagers()
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

void PlaySceneFlow::GameUpdate()
{
	//コインの更新
	coinManager->Update();
	//レーサーの処理
	racerManager->RacerUpdate();
	flyShipManager->Update();
	//発射物の更新
	firingManager->Update();
	//当たり判定処理
	conflictManager->Update();
	//プレイヤーUI
	playerUI->Update();
	//カメラの処理
	camera->Update();
	//シャドウマップの更新
	shadowMap->SetShadowMapErea();
	//レース終了
	if (gameLimitTimer->IsOverLimitTime() || coinManager->GetCoinNowNum() == 0)
	{
		nowProgress = PlaySceeneProgress::playerGoal;
		score = new ResultScore(gameLimitTimer, racerManager);
		//ゴール後の処理をお願い
		postGoalStaging = new PostGoalStaging();
	}
}

void PlaySceneFlow::EndUpdate()
{
	nextSceneType = SceneType::TITLE;
	isEndProccess = true;
}

void PlaySceneFlow::PlayerGoalUpdate()
{
	if (postGoalStaging->Update())
	{
		nowProgress = PlaySceeneProgress::end;
	}
}

void PlaySceneFlow::StartUpdate()
{
	racePrevProccess->Update();
	racerManager->UpDown();
	//コインの更新
	coinManager->Update();
	//カメラの処理
	camera->Update();
	//シャドウマップの更新
	shadowMap->SetShadowMapErea();
	if (racePrevProccess->IsProccesEnd())
	{
		nowProgress = PlaySceeneProgress::game;
		SoundPlayer::Play2DSE(BGMPass);
		gameLimitTimer->Init();
	}
}
