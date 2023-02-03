#include "PlaySceeneFlow.h"
#include "StageManager.h"
#include "PlayerRelatedInfo.h"
#include "Utility.h"
#include "ImgUI.h"
#include "StringUI.h"
#include "SoundPlayer.h"
PlaySceeneFlow::PlaySceeneFlow()
{
	soundPlayer = new SoundPlayer();
	courceDataLoader = new CourceDataLoader();
	nowProgress = PlaySceeneProgress::start;
	stageManager = new StageManager(courceDataLoader);
	racerManager = new RacerManager(3,courceDataLoader);
	camera = new PlaySceneCamera();
	dataCreator = new CreatePosAndDirData();
	countDown = new CountDown();
	postGoalStaging = nullptr;
	miniMap = new MiniMap(minimapX,minimapY, courceDataLoader->GetMiniMapImgAddress());
	conflictProcesser = new ConflictProcesser();
	gimmickObjManager = new GimmickObjManager(conflictProcesser,courceDataLoader);
	playerRelatedUI = new PlayerRelatedUI(maxLap);

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
	SAFE_DELETE(soundPlayer);
}

void PlaySceeneFlow::Update(float deltaTime)
{
	int key = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	VECTOR playerPos = {};
	PlayerRelatedInfo playerRelatedInfo = {};
	switch (nowProgress)
	{
		//スタート処理
	case PlaySceeneProgress::start:
		nowProgress = PlaySceeneProgress::countDown;

		break;
		//カウントダウン
	case PlaySceeneProgress::countDown:
		countDown->Update(deltaTime);
		camera->Update(racerManager->GetPlayerCar());
		racerManager->RacerUpdate(0, stageManager->GetCircuit());
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
		racerManager->RacerUpdate(deltaTime, stageManager->GetCircuit());
		racerManager->RacerConflictProcces(conflictProcesser, stageManager->GetCircuit(), deltaTime);
		racerManager->RacerRankUpdate();
		playerRelatedInfo = racerManager->GetPlayerRelatedInfo();
		playerRelatedInfo.time = raceTime;
		playerRelatedUI->Update(playerRelatedInfo, deltaTime);
		playerPos = racerManager->GetPlayerCar()->GetPos();
		dataCreator->WriteWhereToTurn(playerPos, racerManager->GetPlayerCar()->GetDir());
		//ミニマップ
		miniMap->Update(-playerPos.x, playerPos.z);
		//カメラの処理
		camera->Update(racerManager->GetPlayerCar());

		if (playerRelatedInfo.lap == maxLap)//レース終了
		{
			dataCreator->WritePosAndDir(racerManager->GetPlayerCar()->GetPos(), racerManager->GetPlayerCar()->GetDir());
			nowProgress = PlaySceeneProgress::playerGoal;
			postGoalStaging = new PostGoalStaging();
			scoreTime = new ScoreTime(raceTime);
		}
		break;
	case PlaySceeneProgress::playerGoal:
		
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
