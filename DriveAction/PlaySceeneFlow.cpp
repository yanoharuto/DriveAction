#include "PlaySceeneFlow.h"
#include "StageManager.h"
#include "UIManager.h"
#include "Utility.h"
#include "ImgUI.h"
#include "StringUI.h"
PlaySceeneFlow::PlaySceeneFlow()
{
	courceDataLoader = new CourceDataLoader();
	nowProgress = PlaySceeneProgress::start;
	stageManager = new StageManager(courceDataLoader);
	racerManager = new RacerManager(4,courceDataLoader);
	camera = new PlaySceneCamera();
	timer = new Timer();
	countDown = new CountDown();
	postGoalDirection = nullptr;
	miniMap = new MiniMap(minimapX,minimapY, courceDataLoader->GetMiniMapImgAddress());
	lapUI = new LapUI(maxLap);
	gimmickObjManager = new GimmickObjManager(courceDataLoader);
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
	SAFE_DELETE(lapUI);
	SAFE_DELETE(courceDataLoader);
}

PlaySceeneProgress PlaySceeneFlow::Update()
{
	timer->Update();
	int playerRank=0;
	VECTOR playerPos = {};
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
		}
		break;
		//レース
	case PlaySceeneProgress::race:
		//レーサーの処理
		racerManager->RacerUpdate(timer->GetDeltaTime(), stageManager->GetCircuit());
		racerManager->RacerConflictProcces(timer->GetDeltaTime());
		racerManager->RacerRankUpdate();
		racerManager->GetPlayerRank();
		racerManager->GetPlayerCar()->GetPos();
		//ミニマップ
		miniMap->Update(playerPos.x,-playerPos.z);
		//カメラの処理
		camera->Update(racerManager->GetPlayerCar());
		lapUI->Update(racerManager->GetPlayerGoalCount());
		if (racerManager->GetPlayerGoalCount() == 3)
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
		lapUI->Draw();
		miniMap->Draw();
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

