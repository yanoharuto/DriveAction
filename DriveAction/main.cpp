#include "DxLib.h"
#include "Effect.h"
#include "SceneBase.h"
#include "TitleScene.h"
#include "PlayScene.h"
#include "ResultScene.h"
#include "Utility.h"
#include "UserInput.h"
#include "Broom.h"
SceneBase* MakeScene(SceneType _NowSceneType);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(true);

	// DirectX11���g�p����悤�ɂ���B(DirectX9���A�ꕔ�@�\�s��)
	// Effekseer���g�p����ɂ͕K���ݒ肷��B
	SetUseDirect3DVersion(DX_DIRECT3D_11);

	// ��ʂ̉𑜓x�ƐF�r�b�g�[�x��ݒ�
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32);


	// �P���[�g���ɑ�������l��ݒ肷��
	Set3DSoundOneMetre(16.0f);
	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}
	//Effekseer������������
	if (Effect_Initialize() == -1) 
	{
		DxLib_End();
		return -1;
	}

	//ChangeWindowMode(TRUE);
	//�ЂƂO�̃V�[��
	SceneType prevSceneType = SceneType::TITLE;
	//���̃V�[��
	SceneType nowSceneType = SceneType::TITLE;
	//�V�[���𐶐�
	SceneBase* scene = new TitleScene;

	UserInput* userInput = new UserInput;
	Broom* broom = new Broom;
	//�Q�[�����[�v �G�X�P�[�v�L�[����������I��
	while (ProcessMessage() == 0 && !CheckHitKey(KEY_INPUT_ESCAPE))
	{

#ifdef _DEBUG
		clsDx(); // printfDx �̌��ʂ����Z�b�g���邽�߂̊֐�.
#endif	// ������DEBUG�p�̏������I��.
		//�X�V
	
		nowSceneType = scene->Update();
		Effect_Update();
		userInput->Update();
		ClearDrawScreen();//��ʂ�����������
		scene->Draw();//�`��
		Effect_Draw();
		ScreenFlip();//����ʂ̓��e��\��ʂɔ��f������

		//Update�Ŏ��̃V�[���ɍX�V�����Ȃ�
		if (nowSceneType != prevSceneType)
		{
			SAFE_DELETE(scene);//�V�[���̊J��
			//�V�����V�[���̍쐬
			scene = MakeScene(nowSceneType);
		}
		//���O�̃V�[�����L�^
		prevSceneType = nowSceneType;
	}
	SAFE_DELETE(broom);
	SAFE_DELETE(scene);
	Effect_Finalize();

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}
/// <summary>
/// �V�����g���V�[�����m��
/// </summary>
/// <param name="_NowSceneType"></param>
/// <returns></returns>
SceneBase* MakeScene(SceneType _NowSceneType)
{
	SceneBase* retScene = nullptr;
	switch (_NowSceneType)
	{
	case SceneType::TITLE:
		retScene = new TitleScene;
		break;
	case SceneType::PLAY:
		retScene = new PlayScene;
		break;
	case SceneType::RESULT:
		retScene = new ResultScene;
		break;
	default:
		break;
	}
	return retScene;
}
