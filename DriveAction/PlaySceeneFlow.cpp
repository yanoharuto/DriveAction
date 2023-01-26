#include "PlaySceeneFlow.h"
#include "StageManager.h"
#include "PlayerRelatedInfo.h"
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
}

PlaySceeneProgress PlaySceeneFlow::Update()
{
	timer->Update();
	int playerRank=0;
	VECTOR playerPos = {};
	PlayerRelatedInfo playerRelatedInfo = {};
	switch (nowProgress)
	{
		//�X�^�[�g����
	case PlaySceeneProgress::start:
		nowProgress = PlaySceeneProgress::countDown;

		break;
		//�J�E���g�_�E��
	case PlaySceeneProgress::countDown:
		countDown->Update(timer->GetDeltaTime());
		camera->Update(racerManager->GetPlayerCar());
		racerManager->RacerUpdate(conflictProcesser, 0, stageManager->GetCircuit());
		//�J�E���g�_�E�����I�������
		if (countDown->CountDownEnd())
		{
			SAFE_DELETE(countDown);
			nowProgress = PlaySceeneProgress::race;
		}
		break;
		//���[�X
	case PlaySceeneProgress::race:
		//���[�T�[�̏���
		racerManager->RacerUpdate(conflictProcesser,timer->GetDeltaTime(), stageManager->GetCircuit());
		racerManager->RacerConflictProcces(timer->GetDeltaTime());
		racerManager->RacerRankUpdate();
		playerRelatedInfo = racerManager->GetPlayerRelatedInfo();
		playerRelatedInfo.time = timer->GetScoreTime();
		playerRelatedUI->Update(playerRelatedInfo,timer->GetDeltaTime());
		playerPos = racerManager->GetPlayerCar()->GetPos();
		//�~�j�}�b�v
		miniMap->Update(-playerPos.x,playerPos.z);
		//�J�����̏���
		camera->Update(racerManager->GetPlayerCar());;
		if (playerRelatedInfo.lap == 3)
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

