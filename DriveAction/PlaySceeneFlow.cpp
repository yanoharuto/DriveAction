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
	racerManager = new RacerManager(2,courceDataLoader);
	camera = new PlaySceneCamera();
	timer = new Timer();
	uiManager = new UIManager();
	countDown = new CountDown();
	postGoalDirection = nullptr;
	miniMap = new MiniMap(uiManager,minimapX,minimapY, courceDataLoader->GetMiniMapImgAddress());
	uiData = {};
}

PlaySceeneFlow::~PlaySceeneFlow()
{
	SAFE_DELETE(racerManager);
	SAFE_DELETE(stageManager);
	SAFE_DELETE(camera);
	SAFE_DELETE(uiManager);
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
	std::string count;
	int playerRank=0;
	VECTOR playerPos = {};
	switch (nowProgress)
	{
		//スタート処理
	case PlaySceeneProgress::start:
		nowProgress = PlaySceeneProgress::countDown;
		MakeCountDownUI();

		break;
		//カウントダウン
	case PlaySceeneProgress::countDown:
		count = countDown->Update(timer->GetDeltaTime());
		uiManager->Update(countUINum, count);
		camera->Update(racerManager->GetPlayerCar());
		//カウントダウンが終わったら
		if (countDown->CountDownEnd())
		{
			uiManager->DeleteArgumentUI(countUINum);
			SAFE_DELETE(countDown);
			nowProgress = PlaySceeneProgress::race;
		}
		break;
		//レース
	case PlaySceeneProgress::race:
		racerManager->RacerUpdate(timer->GetDeltaTime(), stageManager->GetCircuit());
		racerManager->RacerConflictProcces();
		racerManager->RacerRankUpdate();
		playerRank = racerManager->GetPlayerRank();
		playerPos = racerManager->GetPlayerCar()->GetPos();
		miniMap->Update(uiManager, playerPos.x,-playerPos.z);
		camera->Update(racerManager->GetPlayerCar());
		if (racerManager->GetPlayerGoalCount() == 1)
		{
			nowProgress = PlaySceeneProgress::playerGoal;
			postGoalDirection = new PostGoalDirection(uiManager);
			scoreTime = new ScoreTime(timer);
		}
		break;
	case PlaySceeneProgress::playerGoal:
		if (postGoalDirection->Update(timer->GetDeltaTime(), uiManager))
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
	racerManager->Draw();
	stageManager->Draw();
	uiManager->DrawUI();
	switch (nowProgress)
	{
	case PlaySceeneProgress::start:
		break;
	case PlaySceeneProgress::countDown:
		break;
	case PlaySceeneProgress::race:
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

void PlaySceeneFlow::MakeCountDownUI()
{
	uiData.x = 350;
	uiData.y = 120;
	uiData.dataHandle = CreateFontToHandle("BIZ UDゴシック", 64, 3, DX_FONTTYPE_NORMAL);
	StringUI* countDownUI = new StringUI(GetColor(230, 0, 0), uiData);
	countUINum = uiManager->AddUI(countDownUI);
}

void PlaySceeneFlow::MakeRankUI()
{
	uiData.x = 1000;
	uiData.y = 200;
	uiData.dataHandle = CreateFontToHandle("BIZ UDゴシック", 64, 3, DX_FONTTYPE_NORMAL);
	StringUI* countDownUI = new StringUI(GetColor(230, 0, 0), uiData);
	
}

