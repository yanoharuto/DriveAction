#include "RaceScreen.h"
#include "Utility.h"
#include "DxLib.h"
//描画した画面
int RaceScreen::screen = -1;
/// <summary>
/// 描画した画像を保存する
/// </summary>
RaceScreen::RaceScreen()
{
    screen = MakeGraph(SCREEN_WIDTH, SCREEN_HEIGHT);
}

RaceScreen::~RaceScreen()
{
}

/// <summary>
/// 描画している画像を更新
/// </summary>
void RaceScreen::ScreenUpdate()
{
    GetDrawScreenGraph(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, screen);
}

int RaceScreen::GetRaceScreen()
{
    return screen;
}
