#include "PlaySceeneFlow.h"
#include "StageManager.h"
#include "PlayerRelatedInfo.h"
#include "Utility.h"
#include "ImgUI.h"
#include "StringUI.h"
#include "SoundPlayer.h"
#include "Rule.h"
PlaySceeneFlow::PlaySceeneFlow()
{
	menu = new  RaceMenu();
	conflictManager = new ConflictManager();
	courceDataLoader = new CourceDataLoader();
	nowProgress = PlaySceeneProgress::start;
	stageManager = new StageManager(courceDataLoader);
	camera = new RaceCamera();

	postGoalStaging = nullptr;

	modelManager = new AssetManager();
	firingManager = new FiringItemManager();
	racerManager = new RacerManager(CPU_RACER_NUM,courceDataLoader);
	playerUI = new PlayerRelatedUI();
	effectManager = new EffectManager();
	flyShipManager = new FlyShipManager(); 
	shadowMap = new ShadowMap();
}

PlaySceeneFlow::~PlaySceeneFlow()
{
	SAFE_DELETE(menu);
	SAFE_DELETE(racerManager)
	SAFE_DELETE(stageManager);
	SAFE_DELETE(camera);
	SAFE_DELETE(courceDataLoader);
	SAFE_DELETE(postGoalStaging);
	SAFE_DELETE(playerUI);
	SAFE_DELETE(score);
	SAFE_DELETE(courceDataLoader);
	SAFE_DELETE(modelManager);
	SAFE_DELETE(firingManager);
	SAFE_DELETE(effectManager);
	SAFE_DELETE(flyShipManager);
	SAFE_DELETE(conflictManager);
	SAFE_DELETE(shadowMap);
}

void PlaySceeneFlow::Update(float deltaTime)
{
	int key = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	PlayerRelatedInfo playerRelatedInfo = PlayerInformationCenter::GetPlayerRelatedInfo(0);
	ObjInfo playerPosAndDir = playerRelatedInfo.objInfo;
	//カメラの処理
	camera->Update(playerPosAndDir, deltaTime);
	switch (nowProgress)
	{
		//スタート処理
	case PlaySceeneProgress::start:
		nowProgress = PlaySceeneProgress::countDown;
		break;
		//カウントダウン
	case PlaySceeneProgress::countDown:
		camera->Update(playerPosAndDir, deltaTime);
		nowProgress = PlaySceeneProgress::race;
		break;
		//レース
	case PlaySceeneProgress::race:
		raceTime += deltaTime;
		//レーサーの処理
		racerManager->RacerUpdate(deltaTime);
		flyShipManager->Update(deltaTime, racerManager->GetPlayerRelatedInfo());
		//発射物の更新
		firingManager->Update(deltaTime);
		conflictManager->Update();
		//プレイヤーに渡す処理
		playerRelatedInfo.scoreTime = MAX_GAME_TIME - raceTime;
		playerUI->Update(playerRelatedInfo, deltaTime);

		//レース終了
		if (playerRelatedInfo.isAlive == false || playerRelatedInfo.scoreTime < 0)
		{
			nowProgress = PlaySceeneProgress::playerGoal;
			postGoalStaging = new PostGoalStaging();
			score = new ResultScore(raceTime,playerRelatedInfo.HP);
			
		}
		break;
	case PlaySceeneProgress::playerGoal:
		//レーサーの処理
		
		//投擲の更新
		firingManager->Update(deltaTime);

		postGoalStaging->Update(deltaTime);
		if (postGoalStaging->Update(deltaTime))
		{
			nowProgress = PlaySceeneProgress::end;
		}
		break;
	case PlaySceeneProgress::end:
		nextSceneType = SceneType::RESULT;
		isEndProccess = true;
		break;
	default:
		nowProgress = PlaySceeneProgress::end;
		break;
	}
	shadowMap->SetShadowMapErea(racerManager->GetPlayerCarPosDir());
#ifdef _DEBUG
#endif
}

void PlaySceeneFlow::Draw()
{	
	shadowMap->SetUP();

	stageManager->Draw();
	firingManager->Draw();
	conflictManager->DrawCollisionSphere();
	racerManager->Draw();
	flyShipManager->Draw();
	switch (nowProgress)
	{
	case PlaySceeneProgress::race:
		playerUI->Draw();
		break;
	case PlaySceeneProgress::playerGoal:
		postGoalStaging->Draw();
		break;
	}
	shadowMap->DrawEnd();

	stageManager->Draw();
	firingManager->Draw();
	conflictManager->DrawCollisionSphere();
	racerManager->Draw();
	flyShipManager->Draw();
	switch (nowProgress)
	{
	case PlaySceeneProgress::race:
		playerUI->Draw();
		break;
	case PlaySceeneProgress::playerGoal:
		postGoalStaging->Draw();
		break;
	}
	shadowMap->Use();
}
