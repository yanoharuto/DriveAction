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
		camera->Update(racerManager->GetPlayer());
		//カウントダウンが終わったら
		if (countDown->CountDownEnd())
		{
			uiManager->DeleteArgumentUI(countUINum);
			nowProgress = PlaySceeneProgress::race;
		}
		break;
		//レース
	case PlaySceeneProgress::race:
		racerManager->RacerUpdate(timer->GetDeltaTime(), stageManager->GetCircuit());
		racerManager->RacerConflictProcces();
		racerManager->RacerRankUpdate();
		playerRank = racerManager->GetPlayerRank();
		playerPos = racerManager->GetPlayer()->GetPos();
		miniMap->Update(uiManager, playerPos.x,-playerPos.z);
		camera->Update(racerManager->GetPlayer());
		if (racerManager->GetPlayerGoalCount() == 1)
		{
			nowProgress = PlaySceeneProgress::playerGoal;
		}
		break;
	case PlaySceeneProgress::playerGoal:
		nowProgress = PlaySceeneProgress::end;
		break;
	case PlaySceeneProgress::end:
		break;
	default:
		nowProgress = PlaySceeneProgress::end;
		break;
	}
#ifdef _DEBUG
	DxLib::printfDx("%d", playerRank);
#endif
	return nowProgress;
}

void PlaySceeneFlow::Draw()
{
	racerManager->Draw();
	stageManager->Draw();
	uiManager->DrawUI();
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

