#include "RaceScreen.h"
#include "Utility.h"
#include "DxLib.h"
int RaceScreen::screen = -1;
RaceScreen::RaceScreen()
{
    screen = MakeGraph(SCREEN_WIDTH, SCREEN_HEIGHT);
}

RaceScreen::~RaceScreen()
{
}

void RaceScreen::SetUp()
{
    GetDrawScreenGraph(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, screen);
}

int RaceScreen::GetRaceScreen()
{
    return screen;
}
