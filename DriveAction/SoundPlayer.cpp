#include "SoundPlayer.h"
#include "DxLib.h"

SoundPlayer::SoundPlayer()
{
}

SoundPlayer::~SoundPlayer()
{
    for (int i = 0; i < soundHandleMap.size(); i++)
    {
        StopSoundMem((*soundHandleMap.begin()).second);
        DeleteSoundMem((*soundHandleMap.begin()).second);
    }
}

void SoundPlayer::SetListener(VECTOR pos, VECTOR front)
{
    Set3DSoundListenerPosAndFrontPos_UpVecY(pos, front);
}

void SoundPlayer::PlaySE(std::string soundFileName)
{
    if (soundHandleMap.contains(soundFileName))
    {
        int handleKey = soundHandleMap[soundFileName];

        PlaySoundMem(handleKey, DX_PLAYTYPE_BACK);

    }
}

void SoundPlayer::Play3DSE(VECTOR pos, std::string soundFileName)
{

    if (soundHandleMap.contains(soundFileName))
    {
        int handleKey = soundHandleMap[soundFileName];
        PlaySoundMem(handleKey, DX_PLAYTYPE_BACK);
    }
}

void SoundPlayer::SetPosition3DSound(VECTOR pos, std::string soundFileName)
{
    if (soundHandleMap.contains(soundFileName))
    {
        int handleKey = soundHandleMap[soundFileName];
        Set3DPositionSoundMem(pos, handleKey);
    }
}



void SoundPlayer::PlayBGM(std::string soundFileName)
{
    if (soundHandleMap.contains(soundFileName))
    {
        int handleKey = soundHandleMap[soundFileName];

        PlaySoundMem(handleKey, DX_PLAYTYPE_LOOP);

    }
}


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

void SoundPlayer::SetSoundVolume(int volumePal, std::string soundFileName)
{
    if (soundHandleMap.contains(soundFileName))
    {
        int handleKey = soundHandleMap[soundFileName];
        if (volumePal != 0)
        {
            
        }
        ChangeVolumeSoundMem(volumePal, handleKey);
    }
}

void SoundPlayer::AddSound(std::string soundFile)
{
    const char* soundFileChar = soundFile.c_str();
    int loadSoundHandleNum = LoadSoundMem(soundFileChar);

    soundHandleMap.insert(std::make_pair(soundFile,loadSoundHandleNum));
}

void SoundPlayer::Add3DSound(std::string soundFileName)
{
    SetCreate3DSoundFlag(true);
    AddSound(soundFileName);
    SetCreate3DSoundFlag(FALSE);
}

void SoundPlayer::SetSoundRadius(int soundRadius, std::string soundFileName)
{
    if (soundHandleMap.contains(soundFileName))
    {
        int handleKey = soundHandleMap[soundFileName];
        float radius = soundRadius;
        // ‰¹‚ª•·‚±‚¦‚é‹——£‚ðÝ’è‚·‚é
        Set3DRadiusSoundMem(radius, handleKey);
    }
}

bool SoundPlayer::IsPlaySound(std::string soundFileName)
{
    return  CheckSoundMem(soundHandleMap[soundFileName]) == 1;
}
