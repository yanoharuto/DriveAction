#pragma once
class Broom
{
public:
    Broom();
    ~Broom();
    void Update();
    void Draw();
private:

    int ColorScreen;	// ���ʂ̕`�挋�ʂ��������ރX�N���[��
    int HighBrightScreen;	// ���ʂ̕`�挋�ʂ��獂�P�x�����𔲂��o�������ʂ��������ރX�N���[��
    int DownScaleScreen;	// ���P�x�������k���������ʂ��������ރX�N���[��
    int GaussScreen;	// �k���摜���K�E�X�t�B���^�łڂ��������ʂ��������ރX�N���[��
    int Angle;		// �J�����̐����p�x
    int StageModel;	// �X�e�[�W���f��
    int GaussRatio;	// �K�E�X�t�B���^�̂ڂ����x����
};

