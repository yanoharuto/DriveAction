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
	courceDataLoader = new CourceDataLoader();
	nowProgress = PlaySceeneProgress::start;
	stageManager = new StageManager(courceDataLoader);
	racerManager = new RacerManager(RACER_NUM,courceDataLoader);
	camera = new RaceCamera();
	
	postGoalStaging = nullptr;
	conflictProcesser = new ConflictProcesser();
	modelManager = new AssetManager();
	firingManager = new FiringItemManager();
	damageObjGene = new DamageObjectGenerator(conflictProcesser,firingManager);
	effectManager = new EffectManager();
}

PlaySceeneFlow::~PlaySceeneFlow()
{
	SAFE_DELETE(menu);
	SAFE_DELETE(racerManager);
	SAFE_DELETE(stageManager);
	SAFE_DELETE(camera);

	SAFE_DELETE(courceDataLoader);
	SAFE_DELETE(postGoalStaging);
	SAFE_DELETE(score);
	SAFE_DELETE(courceDataLoader);
	SAFE_DELETE(conflictProcesser);
	SAFE_DELETE(modelManager);
	SAFE_DELETE(firingManager);
	SAFE_DELETE(effectManager);
}

void PlaySceeneFlow::Update(float deltaTime)
{
	int key = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	PlaySceneCameraArgumentInfo cameraArgumentInfo;
	PlayerRelatedInfo playerRelatedInfo = {};
	switch (nowProgress)
	{
		//スタート処理
	case PlaySceeneProgress::start:
		nowProgress = PlaySceeneProgress::countDown;
		break;
		//カウントダウン
	case PlaySceeneProgress::countDown:
		camera->Update(racerManager->GetPlayerCarPosDir(),deltaTime);
		racerManager->RacerUpdate(0, stageManager->GetCircuit(),damageObjGene);
			nowProgress = PlaySceeneProgress::race;
		
		break;
		//レース
	case PlaySceeneProgress::race:
		raceTime += deltaTime;
		//レーサーの処理
		racerManager->RacerUpdate(deltaTime, stageManager->GetCircuit(),damageObjGene);
		racerManager->RacerConflictProcces(conflictProcesser, stageManager->GetCircuit(), deltaTime);
		racerManager->RacerRankUpdate();
		//投擲の更新
		firingManager->Update(deltaTime);
		firingManager->CircuitTrackConflictProccess(stageManager->GetCircuit());
		//プレイヤーに渡す処理
		playerRelatedInfo = racerManager->GetPlayerRelatedInfo();
		playerRelatedInfo.time = raceTime;
		//カメラにプレイヤーの情報を渡す
		cameraArgumentInfo = racerManager->GetPlayerCarPosDir();
		//カメラの処理
		camera->Update(cameraArgumentInfo, deltaTime);
		
		if (playerRelatedInfo.lap == MAX_LAP)//レース終了
		{
			nowProgress = PlaySceeneProgress::playerGoal;
			postGoalStaging = new PostGoalStaging();
			score = new ResultScore(raceTime,playerRelatedInfo.rank);
			
		}
		break;
	case PlaySceeneProgress::playerGoal:
		//レーサーの処理
		racerManager->RacerUpdate(deltaTime, stageManager->GetCircuit(), damageObjGene);
		racerManager->RacerConflictProcces(conflictProcesser, stageManager->GetCircuit(), deltaTime);
		racerManager->RacerRankUpdate();
		//投擲の更新
		firingManager->Update(deltaTime);
		firingManager->CircuitTrackConflictProccess(stageManager->GetCircuit());
		//カメラにプレイヤーの情報を渡す
		cameraArgumentInfo = racerManager->GetPlayerCarPosDir();
		//カメラの処理
		camera->Update(cameraArgumentInfo, deltaTime);

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
#ifdef _DEBUG
	//DxLib::printfDx("%d", playerRank);
#endif
}

void PlaySceeneFlow::Draw()
{	
	stageManager->Draw();
	racerManager->Draw();
	firingManager->Draw();
	switch (nowProgress)
	{
	case PlaySceeneProgress::start:
		break;
	case PlaySceeneProgress::countDown:
		break;
	case PlaySceeneProgress::race:
		break;
	case PlaySceeneProgress::playerGoal:
		postGoalStaging->Draw();
		break;
	case PlaySceeneProgress::end:
		break;
	default:
		break;
	}
}
