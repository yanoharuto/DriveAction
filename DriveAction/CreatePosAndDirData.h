#pragma once
#include <string>
#include "VectorDataCreator.h"
#include "DxLib.h"
/// <summary>
/// �R�[�X�̃f�[�^�����̂Ɏg��
/// </summary>
class CreatePosAndDirData
{
public:
    CreatePosAndDirData();
    ~CreatePosAndDirData();
    /// <summary>
    /// �Ȃ��鎞�����R�[�X�f�[�^���L�^����
    /// </summary>
    /// <param name="pos"></param>
    /// <param name="dir"></param>
    void WriteWhereToTurn(VECTOR pos,VECTOR dir);
    /// <summary>
    /// �R�[�X�f�[�^���L�^����
    /// </summary>
    /// <param name="pos"></param>
    /// <param name="dir"></param>
    void WritePosAndDir(VECTOR pos,VECTOR dir);
private:
    //�R�[�X��ʂ鎞�̕���
    std::string dirFileName = "CourceDir.txt";
    //�R�[�X��ʂ鎞�̏ꏊ
    std::string posFileName = "CourcePos.txt";
    //�����L�^�W
    VectorDataCreator* dirDataCreator;
    //�ꏊ�L�^�W
    VectorDataCreator* posDataCreator;
    //�Ō�ɋȂ��������̕���
    VECTOR prevVec = {-0.999753,0.00000,-0.022217};
    //�Ȃ���������Ŏg��
    const float turnProccesLine = 3.0f;
};

