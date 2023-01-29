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
	timer = new Timer();
	countDown = new CountDown();
	postGoalDirection = nullptr;
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
	SAFE_DELETE(timer);
	SAFE_DELETE(countDown);
	SAFE_DELETE(courceDataLoader);
	SAFE_DELETE(miniMap);
	SAFE_DELETE(postGoalDirection);
	SAFE_DELETE(scoreTime);
	SAFE_DELETE(courceDataLoader);
	SAFE_DELETE(conflictProcesser);
	SAFE_DELETE(playerRelatedUI);
	SAFE_DELETE(soundPlayer);
}

PlaySceeneProgress PlaySceeneFlow::Update()
{
	timer->Update();
	int playerRank=0;
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
		countDown->Update(timer->GetDeltaTime());
		camera->Update(racerManager->GetPlayerCar());
		racerManager->RacerUpdate(0, stageManager->GetCircuit());
		//カウントダウンが終わったら
		if (countDown->CountDownEnd())
		{
			SAFE_DELETE(countDown);
			nowProgress = PlaySceeneProgress::race;
			gameStartTime = timer->GetScoreTime();
		}
		break;
		//レース
	case PlaySceeneProgress::race:
		//レーサーの処理
		racerManager->RacerUpdate(timer->GetDeltaTime(), stageManager->GetCircuit());
		racerManager->RacerConflictProcces(conflictProcesser, stageManager->GetCircuit(), timer->GetDeltaTime());
		racerManager->RacerRankUpdate();
		playerRelatedInfo = racerManager->GetPlayerRelatedInfo();
		playerRelatedInfo.time = round((timer->GetScoreTime() - gameStartTime) / 10) / 100;
		playerRelatedUI->Update(playerRelatedInfo,timer->GetDeltaTime());
		playerPos = racerManager->GetPlayerCar()->GetPos();
		//ミニマップ
		miniMap->Update(-playerPos.x,playerPos.z);
		//カメラの処理
		camera->Update(racerManager->GetPlayerCar());
		if (playerRelatedInfo.lap == maxLap)
		{
			nowProgress = PlaySceeneProgress::playerGoal;
			postGoalDirection = new PostGoalDirection();
			scoreTime = new ScoreTime(timer);
		}
		break;
	case PlaySceeneProgress::playerGoal:
		if (postGoalDirection->Update(timer->GetDeltaTime()))
		{
			nowProgress = PlaySceeneProgress::end;
		}
		break;
	case PlaySceeneProgress::end:
		break;
	default:
		nowProgress = PlaySceeneProgress::end;
		break;
	}
#ifdef _DEBUG
	//DxLib::printfDx("%d", playerRank);
#endif
	return nowProgress;
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
		postGoalDirection->Draw();
		break;
	case PlaySceeneProgress::end:
		break;
	default:
		break;
	}
}

void PlaySceeneFlow::MakeRankUI()
{
}

