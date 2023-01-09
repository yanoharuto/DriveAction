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
	uiManager = new UIManager();
	countDown = new CountDown();
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
	SAFE_DELETE(courceDataLoader)
}

PlaySceeneProgress PlaySceeneFlow::Update()
{
	timer->Update();
	std::string count;
	switch (nowProgress)
	{
	case PlaySceeneProgress::start:
		nowProgress = PlaySceeneProgress::countDown;
		MakeCountDownUI();
		MakeMiniMapUI();
		break;
	case PlaySceeneProgress::countDown:
		count = countDown->Update(timer->GetDeltaTime());
		uiManager->Update(countUINum, count);
		camera->Update(racerManager->GetPlayer());
		if (countDown->CountDownEnd())
		{
			uiManager->DeleteArgumentUI(countUINum);
			nowProgress = PlaySceeneProgress::race;
		}
		break;
	case PlaySceeneProgress::race:
		racerManager->Update(timer->GetDeltaTime(), stageManager->GetCircuit());
		racerManager->LacerConflictProcces();
		camera->Update(racerManager->GetPlayer());
		break;
	case PlaySceeneProgress::playerGoal:

		break;
	case PlaySceeneProgress::end:
		break;
	default:
		nowProgress = PlaySceeneProgress::end;
		break;
	}
#ifdef  _DEBUG


#endif //  _DEBUG

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
	uiData.dataHandle = CreateFontToHandle("BIZ UDƒSƒVƒbƒN", 64, 3, DX_FONTTYPE_NORMAL);
	StringUI* countDownUI = new StringUI(GetColor(230, 0, 0), uiData);
	countUINum = uiManager->AddUI(countDownUI);
}

void PlaySceeneFlow::MakeMiniMapUI()
{
	uiData.x = 1080;
	uiData.y = 450;
	uiData.dataHandle = LoadGraph(courceDataLoader->GetMiniMapImgAddress().c_str(),true);
	ImgUI* miniMap = new ImgUI(0.4f,uiData);
	mapUINum = uiManager->AddUI(miniMap);
}
