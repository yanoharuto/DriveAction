// �u���[�����ʊ�{
#include "DxLib.h"

#define SCREEN_W		640				// ��ʂ̉���
#define SCREEN_H		480				// ��ʂ̏c��
#define DOWN_SCALE		8				// �K�E�X�t�B���^���|����摜����ʂ̃T�C�Y�̉����̂P��
#define DOWN_SCALE_SCREEN_W	( SCREEN_W / DOWN_SCALE )	// �K�E�X�t�B���^���|����摜�̉���
#define DOWN_SCALE_SCREEN_H	( SCREEN_H / DOWN_SCALE )	// �K�E�X�t�B���^���|����摜�̏c��

int ColorScreen;	// ���ʂ̕`�挋�ʂ��������ރX�N���[��
int HighBrightScreen;	// ���ʂ̕`�挋�ʂ��獂�P�x�����𔲂��o�������ʂ��������ރX�N���[��
int DownScaleScreen;	// ���P�x�������k���������ʂ��������ރX�N���[��
int GaussScreen;	// �k���摜���K�E�X�t�B���^�łڂ��������ʂ��������ރX�N���[��

// WinMain�֐�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	int Angle;		// �J�����̐����p�x
	int StageModel;	// �X�e�[�W���f��
	int GaussRatio;	// �K�E�X�t�B���^�̂ڂ����x����

	// �E�C���h�E���[�h�ŋN��
	ChangeWindowMode(TRUE);

	// ��ʂ̉𑜓x�ƐF�r�b�g�[�x��ݒ�
	SetGraphMode(SCREEN_W, SCREEN_H, 32);

	// �c�w���C�u�����̏�����
	if (DxLib_Init() < 0)
		return -1;

	// �X�e�[�W���f���̓ǂݍ���
	StageModel = MV1LoadModel("BloomTestStage.mqo");

	// �ʏ�̕`�挋�ʂ��������ރX�N���[���ƁA�t�B���^�[�̏������ʂ��������ރX�N���[���̍쐬
	ColorScreen = MakeScreen(SCREEN_W, SCREEN_H, FALSE);
	HighBrightScreen = MakeScreen(SCREEN_W, SCREEN_H, FALSE);
	DownScaleScreen = MakeScreen(DOWN_SCALE_SCREEN_W, DOWN_SCALE_SCREEN_H, FALSE);
	GaussScreen = MakeScreen(DOWN_SCALE_SCREEN_W, DOWN_SCALE_SCREEN_H, FALSE);

	// ClearDrawScreen ���ɉ�ʂɓh��Ԃ��F���Z�b�g( �^���� )
	SetBackgroundColor(255, 255, 255);

	// �J�����̊p�x�ƃK�E�X�t�B���^�̂ڂ����x������������
	Angle = 0;
	GaussRatio = 900;

	// ���C�����[�v(�����L�[�������ꂽ�烋�[�v�𔲂���)
	while (ProcessMessage() == 0)
	{
		// ���E�L�[�������ꂽ��J��������]����
		if (CheckHitKey(KEY_INPUT_LEFT))
		{
			Angle -= 3;
			if (Angle < 0)
			{
				Angle += 360;
			}
		}
		if (CheckHitKey(KEY_INPUT_RIGHT))
		{
			Angle += 3;
			if (Angle > 360)
			{
				Angle -= 360;
			}
		}

		// �㉺�L�[�������ꂽ��K�E�X�t�B���^�̂ڂ����x������ύX����
		if (CheckHitKey(KEY_INPUT_UP))
		{
			GaussRatio++;
		}
		if (CheckHitKey(KEY_INPUT_DOWN))
		{
			if (GaussRatio > 0)
				GaussRatio--;
		}


		// �ʏ�̕`�挋�ʂ��������ރX�N���[����`��Ώۂɂ���
		SetDrawScreen(ColorScreen);

		// ��ʂ��N���A
		ClearDrawScreen();


		// �J�����̈ʒu�ƌ�����ݒ�
		SetCameraPositionAndAngle(VGet(0.0f, 120.0f, 0.0f), 0.0f, Angle / 180.0f * 3.14159f, 0.0f);

		// �X�e�[�W���f���̕`��
		MV1DrawModel(StageModel);


		// �`�挋�ʂ��獂�P�x�����݂̂𔲂��o�����摜�𓾂�
		GraphFilterBlt(ColorScreen, HighBrightScreen, DX_GRAPH_FILTER_BRIGHT_CLIP, DX_CMP_LESS, 230, TRUE, GetColor(0, 0, 0), 255);

		// ���P�x�������W���̂P�ɏk�������摜�𓾂�
		GraphFilterBlt(HighBrightScreen, DownScaleScreen, DX_GRAPH_FILTER_DOWN_SCALE, DOWN_SCALE);

		// �W���̂P�ɏk�������摜���K�E�X�t�B���^�łڂ���
		GraphFilterBlt(DownScaleScreen, GaussScreen, DX_GRAPH_FILTER_GAUSS, 16, GaussRatio);


		// �`��Ώۂ𗠉�ʂɂ���
		SetDrawScreen(DX_SCREEN_BACK);


		// �ʏ�̕`�挋�ʂ�`�悷��
		DrawGraph(0, 0, ColorScreen, FALSE);


		// �`�惂�[�h���o�C���j�A�t�B���^�����O�ɂ���( �g�債���Ƃ��Ƀh�b�g���ڂ₯��悤�ɂ��� )
		SetDrawMode(DX_DRAWMODE_BILINEAR);

		// �`��u�����h���[�h�����Z�ɂ���
		SetDrawBlendMode(DX_BLENDMODE_ADD, 255);

		// ���P�x�������k�����Ăڂ������摜����ʂ����ς��ɂQ��`�悷��( �Q��`�悷��̂͂�薾�邭�݂���悤�ɂ��邽�� )
		DrawExtendGraph(0, 0, SCREEN_W, SCREEN_H, GaussScreen, FALSE);
		DrawExtendGraph(0, 0, SCREEN_W, SCREEN_H, GaussScreen, FALSE);

		// �`��u�����h���[�h���u�����h�����ɖ߂�
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

		// �`�惂�[�h���A���X�g�ɖ߂�
		SetDrawMode(DX_DRAWMODE_NEAREST);


		// �t�B���^�[�����̓r���o�߂�������悤�ɉ�ʉ����ɏk�����ĕ`�悷��
		DrawExtendGraph(180 * 0 + 24, 320, 180 * 0 + 24 + 160, 120 + 320, HighBrightScreen, FALSE);
		DrawExtendGraph(180 * 1 + 24, 320, 180 * 1 + 24 + 160, 120 + 320, DownScaleScreen, FALSE);
		DrawExtendGraph(180 * 2 + 24, 320, 180 * 2 + 24 + 160, 120 + 320, GaussScreen, FALSE);


		// ���݂̃K�E�X�t�B���^�̂ڂ����x������`�悷��
		DrawFormatString(0, 0, GetColor(255, 255, 255), "Gauss:%d", GaussRatio);


		// ����ʂ̓��e��\��ʂɔ��f
		ScreenFlip();
	}

	// �c�w���C�u�����̌�n��
	DxLib_End();

	// �\�t�g�̏I��
	return 0;
}