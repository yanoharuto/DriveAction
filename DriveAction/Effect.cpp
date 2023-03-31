#include "DxLib.h"
#include "EffekseerForDXLib.h"
static int effectResourceHandle; //�G�t�F�N�g���\�[�X
static int grBackgroundHandle; //�w�ʉ摜�\�[�X
static int grFrontHandle; //�O�ʉ摜�\�[�X
static int playtime; //�G�t�F�N�g�̍Đ�����
static float position_x; //�G�t�F�N�g��x���W
static float position_y; //�G�t�F�N�g��y���W
static int playingEffectHandle; //�Đ�����G�t�F�N�g�̃n���h��
//�G�t�F�N�g�̏�����
int Effect_Initialize() {
    // DirectX11���g�p����悤�ɂ���B(DirectX9���A�ꕔ�@�\�s��)
    // Effekseer���g�p����ɂ͕K���ݒ肷��B
    SetUseDirect3DVersion(DX_DIRECT3D_11);
    //Effekseer������������
    if (Effekseer_Init(8000) == -1)
    {
        return -1;
    }
    // �t���X�N���[���E�C���h�E�̐؂�ւ��Ń��\�[�X��������̂�h���B
    // Effekseer���g�p����ꍇ�͕K���ݒ肷��B
    SetChangeScreenModeGraphicsSystemResetFlag(FALSE);
    // DX���C�u�����̃f�o�C�X���X�g�������̃R�[���o�b�N��ݒ肷��B
    // �E�C���h�E�ƃt���X�N���[���̐؂�ւ�����������ꍇ�͕K�����s����B
    // �������ADirectX11���g�p����ꍇ�͎��s����K�v�͂Ȃ��B
    Effekseer_SetGraphicsDeviceLostCallbackFunctions();
    // Z�o�b�t�@��L���ɂ���B
    // Effekseer���g�p����ꍇ�A2D�Q�[���ł�Z�o�b�t�@���g�p����B
    SetUseZBuffer3D(TRUE);
    // Z�o�b�t�@�ւ̏������݂�L���ɂ���B
    // Effekseer���g�p����ꍇ�A2D�Q�[���ł�Z�o�b�t�@���g�p����B
    SetWriteZBuffer3D(TRUE);
    return 0;
}
//�G�t�F�N�g�̍X�V
void Effect_Update() 
{
    // DX���C�u�����̃J������Effekseer�̃J�����𓯊�����B
    Effekseer_Sync3DSetting();
    // Effekseer�ɂ��Đ����̃G�t�F�N�g���X�V����B
    UpdateEffekseer3D();
}
//�G�t�F�N�g�̕`��
void Effect_Draw() {


}
//�G�t�F�N�g�̏I������
void Effect_Finalize() {

    // Effekseer���I������B
    Effkseer_End();
}