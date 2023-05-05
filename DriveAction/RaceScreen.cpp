#include "RaceScreen.h"
#include "Utility.h"
#include "DxLib.h"
//�`�悵�����
int RaceScreen::screen = -1;
/// <summary>
/// �`�悵���摜��ۑ�����
/// </summary>
RaceScreen::RaceScreen()
{
    screen = MakeGraph(SCREEN_WIDTH, SCREEN_HEIGHT);
}

RaceScreen::~RaceScreen()
{
}

/// <summary>
/// �`�悵�Ă���摜���X�V
/// </summary>
void RaceScreen::ScreenUpdate()
{
    GetDrawScreenGraph(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, screen);
}

int RaceScreen::GetRaceScreen()
{
    return screen;
}
