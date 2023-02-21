#include "CountDown.h"
#include "DxLib.h"
#include "Utility.h"
#include "SoundPlayer.h"
#define DOWN_SCALE		8				// �K�E�X�t�B���^���|����摜����ʂ̃T�C�Y�̉����̂P��
CountDown::CountDown()
{
	countDownEnd = false;
	startTime = fiveTime;

	uiData.x = SCREEN_WIDTH / 2;
	uiData.y = SCREEN_HEIGHT / 7;
	highBrightGraph = MakeScreen(256, 256, FALSE);
	gaussGraph = MakeScreen(256, 256, FALSE);;
	uiData.dataHandle = LoadGraph(graphAddress.c_str());
	

	SoundPlayer::LoadSound(countDownSE);
}

CountDown::~CountDown()
{
	SAFE_DELETE(countDownUI);
	DeleteGraph(uiData.dataHandle);
	DeleteGraph(gaussGraph);
	DeleteGraph(highBrightGraph);
	DeleteGraph(lightGraph);
}

void CountDown::Update(float deltaTime)
{
	startTime -= deltaTime;
	switch (static_cast<int>(startTime))
	{
	case 3:
		if (!countStart)
		{
			SoundPlayer::Play2DSE(countDownSE);
			countStart = true;
		}
		color = lightColor1;
		count = "1";
		break;
	case 2:
		color = lightColor2;
		count = "2";
		break;
	case 1:
		color = lightColor3;
		count = "3";
		break;
	case 0:
		countDownEnd = true;
		count = "GO!!";
		break;
	default:
		count = "Count...";
		
		break;
	}
	if (countStart)
	{
		std::string string = lightGraphAddress + count + png;
		lightGraph = LoadGraph(string.c_str());
	}
}

bool CountDown::CountDownEnd()
{
	return countDownEnd;
}

void CountDown::DrawUI()
{
	//���C�g�{�̂�`��
	DrawRotaGraph(uiData.x, uiData.y, 0.5, 0, uiData.dataHandle, true, 0, 0);
	if (countStart)
	{
		//����`��
		DrawRotaGraph(uiData.x, uiData.y, 0.5, 0, lightGraph, true, 0, 0);
		// �`�惂�[�h���o�C���j�A�t�B���^�����O�ɂ���( �g�債���Ƃ��Ƀh�b�g���ڂ₯��悤�ɂ��� )
		SetDrawMode(DX_DRAWMODE_BILINEAR);

		// �`��u�����h���[�h�����Z�ɂ���
		SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
		// �`�挋�ʂ��獂�P�x�����݂̂𔲂��o�����摜�𓾂�
		int success = GraphFilterBlt(lightGraph, highBrightGraph, DX_GRAPH_FILTER_BRIGHT_CLIP, DX_CMP_GREATER, 30, TRUE, color, 200);
		// �W���̂P�ɏk�������摜���K�E�X�t�B���^�łڂ���
		success = GraphFilterBlt(highBrightGraph, gaussGraph, DX_GRAPH_FILTER_GAUSS, 16, gaussRatio);

		// ���P�x�������k�����Ăڂ������摜����ʂ����ς��ɂQ��`�悷��( �Q��`�悷��̂͂�薾�邭�݂���悤�ɂ��邽�� )
		DrawRotaGraph(uiData.x, uiData.y, 3, 0, gaussGraph, true, 0, 0);

		// �`��u�����h���[�h���u�����h�����ɖ߂�
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

		// �`�惂�[�h���A���X�g�ɖ߂�
		SetDrawMode(DX_DRAWMODE_NEAREST);
	}
}