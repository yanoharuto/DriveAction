#pragma once
#include <map>
#include <string>
#include"DxLib.h"
class SoundPlayer
{
public:
    /// <summary>
    /// 音を出すやつ
    /// </summary>
    SoundPlayer();
    /// <summary>
    /// 音を全部止めて消す
    /// </summary>
    ~SoundPlayer();
    /// <summary>
    /// 3Ⅾの音を聞くために座標とかを更新してもらう
    /// </summary>
    /// <param name="pos"></param>
    /// <param name="front"></param>
    static void SetListener(VECTOR pos,VECTOR front);
    /// <summary>
    /// 効果音を鳴らす
    /// </summary>
    /// <param name="soundFileName"></param>
    static void Play2DSE(std::string soundFileName);
    /// <summary>
    /// 3d空間での音を鳴らす
    /// </summary>
    /// <param name="pos"></param>
    /// <param name="soundFileName"></param>
    static void Play3DSE( std::string soundFileName);
    /// <summary>
    /// 鳴らしたい音の位置を変える
    /// </summary>
    /// <param name="pos"></param>
    /// <param name="soundFileName"></param>
    static void SetPosition3DSound(VECTOR pos, std::string soundFileName);
    /// <summary>
    /// BGMを鳴らす
    /// </summary>
    /// <param name="soundFileName"></param>
    static void PlayBGM(std::string soundFileName);
    /// <summary>
    /// 音を止める
    /// </summary>
    /// <param name="soundFileName"></param>
    static void StopSound(std::string soundFileName);
    /// <summary>
    /// 全ての音を止める
    /// </summary>
    /// <param name="soundFileName"></param>
    static void StopAllSound();
    /// <summary>
    /// 音量を設定する
    /// </summary>
    /// <param name="volumePal"></param>
    /// <param name="soundFileName"></param>
    static void SetSoundVolume(int volumePal,std::string soundFileName);
    /// <summary>
    /// 音をロードして使いまわせるようにする
    /// </summary>
    /// <param name="soundFileName"></param>
    static void LoadSound(std::string soundFileName);
    /// <summary>
    /// 音をロードして使いまわせるようにする
    /// </summary>
    /// <param name="soundFileName"></param>
    static void Load3DSound(std::string soundFileName);
    /// <summary>
    /// 音が聞こえる半径を決める
    /// </summary>
    /// <param name="soundRadius"></param>
    /// <param name="soundFileName"></param>
    static void SetSoundRadius(int soundRadius, std::string soundFileName);
    /// <summary>
    /// その音が鳴ってるかどうか調べる
    /// </summary>
    /// <param name="soundFileName"></param>
    /// <returns></returns>
    static bool IsPlaySound(std::string soundFileName);
    
private:
    static std::map<std::string, int> soundHandleMap;
};

