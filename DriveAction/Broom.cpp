#include "Broom.h"
#include "Utility.h"
#include "DxLib.h"
#define DOWN_SCALE		8				// �K�E�X�t�B���^���|����摜����ʂ̃T�C�Y�̉����̂P��
#define DOWN_SCALE_SCREEN_W	( SCREEN_WIDTH / DOWN_SCALE )	// �K�E�X�t�B���^���|����摜�̉���
#define DOWN_SCALE_SCREEN_H	( SCREEN_HEIGHT / DOWN_SCALE )	// �K�E�X�t�B���^���|����摜�̏c��

Broom::Broom()
{
	// �ʏ�̕`�挋�ʂ��������ރX�N���[���ƁA�t�B���^�[�̏������ʂ��������ރX�N���[���̍쐬
	ColorScreen = MakeScreen(SCREEN_WIDTH, SCREEN_HEIGHT, FALSE);
	HighBrightScreen = MakeScreen(SCREEN_WIDTH, SCREEN_HEIGHT, FALSE);
	DownScaleScreen = MakeScreen(DOWN_SCALE_SCREEN_W, DOWN_SCALE_SCREEN_H, FALSE);
	GaussScreen = MakeScreen(DOWN_SCALE_SCREEN_W, DOWN_SCALE_SCREEN_H, FALSE);
	// �J�����̊p�x�ƃK�E�X�t�B���^�̂ڂ����x������������
	Angle = 0;
	GaussRatio = 900;
}

Broom::~Broom()
{
}

void Broom::Update()
{
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
	// �J�����̈ʒu�ƌ�����ݒ�
	SetCameraPositionAndAngle(VGet(0.0f, 120.0f, 0.0f), 0.0f, Angle / 180.0f * 3.14159f, 0.0f);
	// �ʏ�̕`�挋�ʂ��������ރX�N���[����`��Ώۂɂ���
	SetDrawScreen(ColorScreen);
}

void Broom::Draw()
{
	// �`�挋�ʂ��獂�P�x�����݂̂𔲂��o�����摜�𓾂�
	int success = GraphFilterBlt(ColorScreen, HighBrightScreen, DX_GRAPH_FILTER_BRIGHT_CLIP, DX_CMP_LESS, 230, TRUE, GetColor(0, 0, 0), 255);

	// ���P�x�������W���̂P�ɏk�������摜�𓾂�
	success = GraphFilterBlt(HighBrightScreen, DownScaleScreen, DX_GRAPH_FILTER_DOWN_SCALE, DOWN_SCALE);

	// �W���̂P�ɏk�������摜���K�E�X�t�B���^�łڂ���
	success = GraphFilterBlt(DownScaleScreen, GaussScreen, DX_GRAPH_FILTER_GAUSS, 16, GaussRatio);

	// �ʏ�̕`�挋�ʂ�`�悷��
	DrawGraph(0, 0, ColorScreen, FALSE);

	// �`�惂�[�h���o�C���j�A�t�B���^�����O�ɂ���( �g�債���Ƃ��Ƀh�b�g���ڂ₯��悤�ɂ��� )
	SetDrawMode(DX_DRAWMODE_BILINEAR);

	// �`��u�����h���[�h�����Z�ɂ���
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);

	// ���P�x�������k�����Ăڂ������摜����ʂ����ς��ɂQ��`�悷��( �Q��`�悷��̂͂�薾�邭�݂���悤�ɂ��邽�� )
	DrawExtendGraph(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, GaussScreen, FALSE);
	DrawExtendGraph(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, GaussScreen, FALSE);

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
}
