#include "PlaySceeneFlow.h"
#include "Utility.h"
PlaySceeneFlow::PlaySceeneFlow()
{
}

PlaySceeneFlow::~PlaySceeneFlow()
{
	SAFE_DELETE(lacerManager);
	SAFE_DELETE(camera);
	SAFE_DELETE(skyDome);
	SAFE_DELETE(circuit);
	SAFE_DELETE(timer);
}

PlaySceeneFlowMode PlaySceeneFlow::Update()
{
	timer->Update();
	switch (nowMode)
	{
	case PlaySceeneFlowMode::start:
		nowMode = PlaySceeneFlowMode::countDown;
		break;
	case PlaySceeneFlowMode::countDown:
		nowMode = PlaySceeneFlowMode::race;
		break;
	case PlaySceeneFlowMode::race:
		lacerManager->Update(timer->GetDeltaTime(), circuit);
		lacerManager->LacerConflictProcces();
		camera->Update(lacerManager->GetPlayer());
		break;
	case PlaySceeneFlowMode::playerGoal:
		break;
	case PlaySceeneFlowMode::end:
		break;
	default:
		nowMode = PlaySceeneFlowMode::end;
		break;
	}
	return nowMode;
}

void PlaySceeneFlow::Draw()
{
}
