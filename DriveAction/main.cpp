#include "DxLib.h"
#include "SceneBase.h"
#include "TitleScene.h"
#include "PlayScene.h"
#include "ResultScene.h"
#include "Utility.h"
#include "UserInput.h"

SceneBase* MakeScene(SceneType _NowSceneType);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}
	// ��ʃ��[�h�̃Z�b�g.
	SetGraphMode(640, 480, 16);
	ChangeWindowMode(TRUE);

	//�ЂƂO�̃V�[��
	SceneType prevSceneType = SceneType::TITLE;
	//���̃V�[��
	SceneType nowSceneType = SceneType::TITLE;
	//�V�[���𐶐�
	SceneBase* scene = new TitleScene;

	UserInput* userInput = new UserInput;

	//�Q�[�����[�v �G�X�P�[�v�L�[����������I��
	while (ProcessMessage() == 0 && !CheckHitKey(KEY_INPUT_ESCAPE))
	{
		//�X�V
		nowSceneType = scene->Update();
		userInput->Update();

#ifdef _DEBUG
		clsDx(); // printfDx �̌��ʂ����Z�b�g���邽�߂̊֐�.

#endif	// ������DEBUG�p�̏������I��.

		ClearDrawScreen();//��ʂ�����������
		scene->Draw();//�`��
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
