#include "PlaySceeneFlow.h"
#include "StageManager.h"
#include "PlayerRelatedInfo.h"
#include "Utility.h"
#include "ImgUI.h"
#include "StringUI.h"
#include "SoundPlayer.h"

PlaySceeneFlow::PlaySceeneFlow()
{
	SoundPlayer::LoadSound(clapSE);
	courceDataLoader = new CourceDataLoader();
	nowProgress = PlaySceeneProgress::start;
	stageManager = new StageManager(courceDataLoader);
	racerManager = new RacerManager(racerNum,courceDataLoader);
	camera = new RaceCamera();
	dataCreator = new CreatePosAndDirData();
	countDown = new CountDown();
	postGoalStaging = nullptr;
	miniMap = new MiniMap(courceDataLoader->GetStageDataGenericAddress());
	conflictProcesser = new ConflictProcesser();
	gimmickObjManager = new GimmickObjManager(conflictProcesser,courceDataLoader);
	playerRelatedUI = new PlayerRelatedUI(maxLap);
	assetManager = new AssetManager();
	firingManager = new FiringItemManager();
	damageObjGene = new DamageObjectGenerator(conflictProcesser,firingManager);
	effectManager = new EffectManager();
}

PlaySceeneFlow::~PlaySceeneFlow()
{
	SAFE_DELETE(racerManager);
	SAFE_DELETE(stageManager);
	SAFE_DELETE(camera);
	SAFE_DELETE(dataCreator);
	SAFE_DELETE(countDown);
	SAFE_DELETE(courceDataLoader);
	SAFE_DELETE(miniMap);
	SAFE_DELETE(postGoalStaging);
	SAFE_DELETE(scoreTime);
	SAFE_DELETE(courceDataLoader);
	SAFE_DELETE(conflictProcesser);
	SAFE_DELETE(playerRelatedUI);
	SAFE_DELETE(assetManager);
	SAFE_DELETE(firingManager);
	SAFE_DELETE(effectManager);
}

void PlaySceeneFlow::Update(float deltaTime)
{
	int key = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	PlaySceneCameraArgumentInfo cameraArgumentInfo;
	PlayerRelatedInfo playerRelatedInfo = {};
	gimmickObjManager->Updatee(deltaTime);
	switch (nowProgress)
	{
		//スタート処理
	case PlaySceeneProgress::start:
		nowProgress = PlaySceeneProgress::countDown;
		break;
		//カウントダウン
	case PlaySceeneProgress::countDown:
		countDown->Update(deltaTime);
		camera->Update(racerManager->GetPlayerCarPosDir(),deltaTime);
		racerManager->RacerUpdate(0, stageManager->GetCircuit(),damageObjGene);
		//カウントダウンが終わったら
		if (countDown->CountDownEnd())
		{
			SAFE_DELETE(countDown);
			nowProgress = PlaySceeneProgress::race;
		}
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
		playerRelatedUI->Update(playerRelatedInfo, deltaTime);
		//カメラにプレイヤーの情報を渡す
		cameraArgumentInfo = racerManager->GetPlayerCarPosDir();
		//カメラの処理
		camera->Update(cameraArgumentInfo, deltaTime);
		//ミニマップ
		miniMap->Update(-cameraArgumentInfo.pos.x, cameraArgumentInfo.pos.z);
		
		if (playerRelatedInfo.lap == maxLap)//レース終了
		{
			nowProgress = PlaySceeneProgress::playerGoal;
			postGoalStaging = new PostGoalStaging();
			scoreTime = new ResultScore(raceTime,playerRelatedInfo.rank);
			SoundPlayer::Play2DSE(clapSE);
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
	gimmickObjManager->Draw();
	firingManager->Draw();
	switch (nowProgress)
	{
	case PlaySceeneProgress::start:
		break;
	case PlaySceeneProgress::countDown:
		countDown->DrawUI();
		break;
	case PlaySceeneProgress::race:
		miniMap->Draw();
		playerRelatedUI->Draw();
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
