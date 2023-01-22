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
		//カウントダウンが終わったら
		if (countDown->CountDownEnd())
		{
			SAFE_DELETE(countDown);
			nowProgress = PlaySceeneProgress::race;
		}
		break;
		//レース
	case PlaySceeneProgress::race:
		racerManager->RacerUpdate(timer->GetDeltaTime(), stageManager->GetCircuit());
		racerManager->RacerConflictProcces(timer->GetDeltaTime());
		racerManager->RacerRankUpdate();
		playerRank = racerManager->GetPlayerRank();
		playerPos = racerManager->GetPlayerCar()->GetPos();
		miniMap->Update(playerPos.x,-playerPos.z);
		camera->Update(racerManager->GetPlayerCar());
		if (racerManager->GetPlayerGoalCount() == 1)
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
	switch (nowProgress)
	{
	case PlaySceeneProgress::start:
		break;
	case PlaySceeneProgress::countDown:
		countDown->DrawUI();
		break;
	case PlaySceeneProgress::race:
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

