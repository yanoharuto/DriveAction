#include "SoundPlayer.h"
#include "DxLib.h"
std::map<std::string, int> SoundPlayer::soundHandleMap;
/// <summary>
/// 音を出すやつ
/// </summary>
SoundPlayer::SoundPlayer()
{
}
/// <summary>
/// デストラクタ
/// </summary>
SoundPlayer::~SoundPlayer()
{
    for (int i = 0; i < soundHandleMap.size(); i++)
    {
        int success= StopSoundMem((*soundHandleMap.begin()).second);
        success = DeleteSoundMem((*soundHandleMap.begin()).second);
        success;
    }
}

/// <summary>
/// 3Ⅾの音を聞くために座標とかを更新してもらう
/// </summary>
/// <param name="pos"></param>
/// <param name="front"></param>
void SoundPlayer::SetListener(VECTOR pos, VECTOR front)
{
    Set3DSoundListenerPosAndFrontPos_UpVecY(pos, front);
}
/// <summary>
/// 効果音を鳴らす
/// </summary>
/// <param name="soundFileName"></param>
void SoundPlayer::Play2DSE(std::string soundFileName)
{
    if (soundHandleMap.contains(soundFileName))
    {
        int handleKey = soundHandleMap[soundFileName];

        PlaySoundMem(handleKey, DX_PLAYTYPE_BACK);

    }
}
/// <summary>
/// 3d空間での音を鳴らす
/// </summary>
/// <param name="pos"></param>
/// <param name="soundFileName"></param>
void SoundPlayer::Play3DSE(std::string soundFileName)
{
    if (soundHandleMap.contains(soundFileName))
    {
        int handleKey = soundHandleMap[soundFileName];
        PlaySoundMem(handleKey, DX_PLAYTYPE_BACK);
    }
}
/// <summary>
/// 鳴らしたい音の位置を変える
/// </summary>
/// <param name="pos"></param>
/// <param name="soundFileName"></param>
void SoundPlayer::SetPosition3DSound(VECTOR pos, std::string soundFileName)
{
    if (soundHandleMap.contains(soundFileName))
    {
        int handleKey = soundHandleMap[soundFileName];
        Set3DPositionSoundMem(pos, handleKey);
    }
}


/// <summary>
/// BGMを鳴らす
/// </summary>
/// <param name="soundFileName"></param>
void SoundPlayer::PlayBGM(std::string soundFileName)
{
    int a;
    if (soundHandleMap.contains(soundFileName))
    {
        int handleKey = soundHandleMap[soundFileName];

        a= PlaySoundMem(handleKey, DX_PLAYTYPE_LOOP);

    }
}
/// <summary>
/// 音を止める
/// </summary>
/// <param name="soundFileName"></param>
void SoundPlayer::StopSound(std::string soundFileName)
{
    if (soundHandleMap.contains(soundFileName))
    {
        int handleKey = soundHandleMap[soundFileName];
        if (CheckSoundMem(handleKey)==1)
        {
            StopSoundMem(handleKey);
        }
    }
}
/// <summary>
/// 全ての音を止める
/// </summary>
/// <param name="soundFileName"></param>
void SoundPlayer::StopAllSound()
{
    for (auto ite = soundHandleMap.begin(); ite != soundHandleMap.end(); ite++)
    {
        StopSound((*ite).first);
    }
}
/// <summary>
/// 音量を設定する
/// </summary>
/// <param name="volumePal"></param>
/// <param name="soundFileName"></param>
void SoundPlayer::SetSoundVolume(int volumePal, std::string soundFileName)
{
    if (soundHandleMap.contains(soundFileName))
    {
        int handleKey = soundHandleMap[soundFileName];

        ChangeVolumeSoundMem(volumePal, handleKey);
    }
}
/// <summary>
/// 音をロードして使いまわせるようにする
/// </summary>
/// <param name="soundFileName"></param>
void SoundPlayer::LoadSound(std::string soundFile)
{
    if (!soundHandleMap.contains(soundFile))
    {
        std::string soundFileName = "data/sound/" + soundFile;
        const char* soundFileChar = soundFileName.c_str();
        int loadSoundHandleNum = LoadSoundMem(soundFileChar);

        soundHandleMap.insert(std::make_pair(soundFile, loadSoundHandleNum));
        SetSoundVolume(60, soundFile);
    }
}
/// <summary>
/// 音をロードして使いまわせるようにする
/// </summary>
/// <param name="soundFileName"></param>
void SoundPlayer::Load3DSound(std::string soundFileName)
{
    SetCreate3DSoundFlag(true);
    LoadSound(soundFileName);
    SetCreate3DSoundFlag(FALSE);
}
/// <summary>
/// 音が聞こえる半径を決める
/// </summary>
/// <param name="soundRadius"></param>
/// <param name="soundFileName"></param>
void SoundPlayer::SetSoundRadius(int soundRadius, std::string soundFileName)
{
    if (soundHandleMap.contains(soundFileName))
    {
        int handleKey = soundHandleMap[soundFileName];
        float radius = soundRadius;
        // 音が聞こえる距離を設定する
        Set3DRadiusSoundMem(radius, handleKey);
    }
}
/// <summary>
/// その音が鳴ってるかどうか調べる
/// </summary>
/// <param name="soundFileName"></param>
/// <returns></returns>
bool SoundPlayer::IsPlaySound(std::string soundFileName)
{
    return  CheckSoundMem(soundHandleMap[soundFileName]) == 1;
}
