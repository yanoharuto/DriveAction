#pragma once

#include <string>
#include <map>
#include"DxLib.h"
class SoundPlayer
{
public:
    /// <summary>
    /// 音を出すやつ
    /// </summary>
    SoundPlayer();
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~SoundPlayer();
    void SetListener(VECTOR pos,VECTOR front);
    /// <summary>
    /// 効果音を鳴らす
    /// </summary>
    /// <param name="soundFileName"></param>
    void PlaySE(std::string soundFileName);
    void Play3DSE(VECTOR pos, std::string soundFileName);
    void SetPosition3DSound(VECTOR pos, std::string soundFileName);
    /// <summary>
    /// BGMを鳴らす
    /// </summary>
    /// <param name="soundFileName"></param>
    void PlayBGM(std::string soundFileName);
    /// <summary>
    /// 音を止める
    /// </summary>
    /// <param name="soundFileName"></param>
    void StopSound(std::string soundFileName);
    /// <summary>
    /// 音量を設定する
    /// </summary>
    /// <param name="volumePal"></param>
    /// <param name="soundFileName"></param>
    void SetSoundVolume(int volumePal,std::string soundFileName);
    /// <summary>
    /// 音をロードして使いまわせるようにする
    /// </summary>
    /// <param name="soundFileName"></param>
    void AddSound(std::string soundFileName);
    void Add3DSound(std::string soundFileName);
    void SetSoundRadius(int soundRadius, std::string soundFileName);
    /// <summary>
    /// その音が鳴ってるかどうか調べる
    /// </summary>
    /// <param name="soundFileName"></param>
    /// <returns></returns>
    bool IsPlaySound(std::string soundFileName);
    
private:
    std::map<std::string,int> soundHandleMap;
};

