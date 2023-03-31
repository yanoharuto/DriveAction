#include "PlaySceneFlow.h"
#include "StageManager.h"
#include "PlayerRelatedInfo.h"
#include "Utility.h"
#include "ImgUI.h"
#include "StringUI.h"
#include "SoundPlayer.h"
#include "Rule.h"
#include "EffekseerForDXLib.h"
PlaySceeneFlow::PlaySceeneFlow()
{

	conflictManager = new ConflictManager();
	courceDataLoader = new CourceDataLoader();
	nowProgress = PlaySceeneProgress::start;
	stageManager = new StageManager();
	camera = new RaceCamera();
	timer = new Timer(MAX_GAME_TIME);
	postGoalStaging = nullptr;
	modelManager = new AssetManager();
	firingManager = new FiringItemManager();
	racerManager = new RacerManager(CPU_RACER_NUM,courceDataLoader);
	coinManager = new CoinManager();
	playerUI = new PlayerRelatedUI(timer,coinManager->GetCoinFirstNum());
	effectManager = new EffectManager();
	flyShipManager = new FlyShipManager(); 
	shadowMap = new ShadowMap();
	racePrevProccess = new RacePrevProcess();
	countDown=new CountDown(timer);
	SoundPlayer::LoadSound(BGMPass);
	SoundPlayer::SetSoundVolume(BGMBolume, BGMPass);
#ifdef _DEBUG
#endif
}

PlaySceeneFlow::~PlaySceeneFlow()
{
	
	SAFE_DELETE(racerManager)
	SAFE_DELETE(stageManager);
	SAFE_DELETE(camera);
	SAFE_DELETE(courceDataLoader);
	SAFE_DELETE(postGoalStaging);
	SAFE_DELETE(playerUI);
	SAFE_DELETE(score);
	SAFE_DELETE(courceDataLoader);
	SAFE_DELETE(modelManager);
	SAFE_DELETE(firingManager);
	SAFE_DELETE(effectManager);
	SAFE_DELETE(flyShipManager);
	SAFE_DELETE(conflictManager);
	SAFE_DELETE(shadowMap);
	SAFE_DELETE(racePrevProccess);
	SAFE_DELETE(coinManager);
	SAFE_DELETE(timer);
	SAFE_DELETE(countDown);
#ifdef _DEBUG
#endif

}

void PlaySceeneFlow::Update()
{
	
	int key = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	PlayerRelatedInfo playerRelatedInfo = PlayerInformationCenter::GetPlayerRelatedInfo(0);
	ObjInfo playerPosAndDir = playerRelatedInfo.objInfo;
	stageManager->Update();
	switch (nowProgress)
	{
		//スタート処理
	case PlaySceeneProgress::start:
		racePrevProccess->Update();
		racerManager->UpDown();
		if (racePrevProccess->IsProccesEnd())
		{
			nowProgress = PlaySceeneProgress::race;
			SoundPlayer::Play2DSE(BGMPass);
		}
		break;
		//レース
	case PlaySceeneProgress::race:
		//コインの更新
		coinManager->Update();

		timer->Update();
		//レーサーの処理
		racerManager->RacerUpdate();
		flyShipManager->Update( racerManager->GetPlayerRelatedInfo());
		//発射物の更新
		firingManager->Update();
		//当たり判定処理
		conflictManager->Update();
		//プレイヤーUI
		playerUI->Update(playerRelatedInfo,coinManager->GetCoinPosList());
		countDown->Update();
		//レース終了
		if (timer->IsOverLimitTime() || coinManager->GetCoinNowNum() == 0)
		{
			nowProgress = PlaySceeneProgress::playerGoal;
			score = new ResultScore(timer, playerRelatedInfo);
			//ゴール後の処理をお願い
			postGoalStaging = new PostGoalStaging();
		}
		break;
	case PlaySceeneProgress::playerGoal:

		//ゴール後の処理更新
		postGoalStaging->Update();
		if (postGoalStaging->Update())
		{
			nowProgress = PlaySceeneProgress::end;
		}
		break;
	case PlaySceeneProgress::end:
		nextSceneType = SceneType::TITLE;
		isEndProccess = true;
		break;
	default:
		nowProgress = PlaySceeneProgress::end;
		break;
	}
	//カメラの処理
	camera->Update(playerPosAndDir);
	shadowMap->SetShadowMapErea(racerManager->GetPlayerCarPosDir());
#ifdef _DEBUG
#endif
}

void PlaySceeneFlow::Draw()
{	
	shadowMap->SetUP();
	ManagerDraw();
	shadowMap->DrawEnd();
	ManagerDraw();
	switch (nowProgress)
	{
	case PlaySceeneProgress::start:
		racePrevProccess->Draw();
	case PlaySceeneProgress::race:
		// Effekseerにより再生中のエフェクトを描画する。
		DrawEffekseer3D();
		playerUI->Draw();
		countDown->DrawUI();
		break;
	case PlaySceeneProgress::playerGoal:
	case PlaySceeneProgress::end:
		postGoalStaging->Draw();
		break;
	}
	shadowMap->Use();
#ifdef DEBUG
	conflictManager->DrawCollisionSphere();
#endif // DEBUG

}

void PlaySceeneFlow::ManagerDraw()
{
	if (nowProgress != PlaySceeneProgress::playerGoal)
	{
		firingManager->Draw();
		racerManager->Draw();
		flyShipManager->Draw();
		stageManager->Draw();
		coinManager->Draw();
	}
}