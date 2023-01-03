#include "PlaySceeneFlow.h"
#include "StageManager.h"
#include "UIManager.h"
#include "Utility.h"
PlaySceeneFlow::PlaySceeneFlow()
{
	nowProgress = PlaySceeneProgress::start;
	lacerManager = new LacerManager(4);
	camera = new PlaySceneCamera();
	timer = new Timer();
	uiManager = new UIManager();
	stageManager = new StageManager(lacerManager->GetPlayer()->GetRadius());
}

PlaySceeneFlow::~PlaySceeneFlow()
{
	SAFE_DELETE(lacerManager);
	SAFE_DELETE(camera);
	SAFE_DELETE(uiManager);
	SAFE_DELETE(timer);
}

PlaySceeneProgress PlaySceeneFlow::Update()
{
	timer->Update();
	switch (nowProgress)
	{
	case PlaySceeneProgress::start:
		nowProgress = PlaySceeneProgress::countDown;
		break;
	case PlaySceeneProgress::countDown:
		nowProgress = PlaySceeneProgress::race;
		break;
	case PlaySceeneProgress::race:
		lacerManager->Update(timer->GetDeltaTime(), stageManager->GetCircuit());
		lacerManager->LacerConflictProcces();
		camera->Update(lacerManager->GetPlayer());
		break;
	case PlaySceeneProgress::playerGoal:
		break;
	case PlaySceeneProgress::end:
		break;
	default:
		nowProgress = PlaySceeneProgress::end;
		break;
	}
	return nowProgress;
}

void PlaySceeneFlow::Draw()
{
	lacerManager->Draw();
	stageManager->Draw();
	uiManager->DrawUI();
}
