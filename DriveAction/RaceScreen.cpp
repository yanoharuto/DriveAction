#include "RaceScreen.h"
#include "Utility.h"
#include "DxLib.h"
//•`‰æ‚µ‚½‰æ–Ê
int RaceScreen::screen = -1;
/// <summary>
/// •`‰æ‚µ‚½‰æ‘œ‚ğ•Û‘¶‚·‚é
/// </summary>
RaceScreen::RaceScreen()
{
    screen = MakeGraph(SCREEN_WIDTH, SCREEN_HEIGHT);
}

RaceScreen::~RaceScreen()
{
}

/// <summary>
/// •`‰æ‚µ‚Ä‚¢‚é‰æ‘œ‚ğXV
/// </summary>
void RaceScreen::ScreenUpdate()
{
    GetDrawScreenGraph(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, screen);
}

int RaceScreen::GetRaceScreen()
{
    return screen;
}
