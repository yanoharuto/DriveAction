#pragma once

#include <string>
#include <map>
#include"DxLib.h"
class SoundPlayer
{
public:
    /// <summary>
    /// �����o�����
    /// </summary>
    SoundPlayer();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~SoundPlayer();
    void SetListener(VECTOR pos,VECTOR front);
    /// <summary>
    /// ���ʉ���炷
    /// </summary>
    /// <param name="soundFileName"></param>
    void PlaySE(std::string soundFileName);
    /// <summary>
    /// 3d��Ԃł̉���炷
    /// </summary>
    /// <param name="pos"></param>
    /// <param name="soundFileName"></param>
    void Play3DSE( std::string soundFileName);
    /// <summary>
    /// �炵�������̈ʒu��ς���
    /// </summary>
    /// <param name="pos"></param>
    /// <param name="soundFileName"></param>
    void SetPosition3DSound(VECTOR pos, std::string soundFileName);
    /// <summary>
    /// BGM��炷
    /// </summary>
    /// <param name="soundFileName"></param>
    void PlayBGM(std::string soundFileName);
    /// <summary>
    /// �����~�߂�
    /// </summary>
    /// <param name="soundFileName"></param>
    void StopSound(std::string soundFileName);
    /// <summary>
    /// ���ʂ�ݒ肷��
    /// </summary>
    /// <param name="volumePal"></param>
    /// <param name="soundFileName"></param>
    void SetSoundVolume(int volumePal,std::string soundFileName);
    /// <summary>
    /// �������[�h���Ďg���܂킹��悤�ɂ���
    /// </summary>
    /// <param name="soundFileName"></param>
    void AddSound(std::string soundFileName);
    /// <summary>
    /// �������[�h���Ďg���܂킹��悤�ɂ���
    /// </summary>
    /// <param name="soundFileName"></param>
    void Add3DSound(std::string soundFileName);
    /// <summary>
    /// �����������锼�a�����߂�
    /// </summary>
    /// <param name="soundRadius"></param>
    /// <param name="soundFileName"></param>
    void SetSoundRadius(int soundRadius, std::string soundFileName);
    /// <summary>
    /// ���̉������Ă邩�ǂ������ׂ�
    /// </summary>
    /// <param name="soundFileName"></param>
    /// <returns></returns>
    bool IsPlaySound(std::string soundFileName);
    
private:
    std::map<std::string,int> soundHandleMap;
};

