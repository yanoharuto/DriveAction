#pragma once
#include <string>
#include "UIManager.h"

#define TIMER_FONT_NUM 10
/// <summary>
/// 数字を描画する
/// </summary>
class NumUI
{
public:
    NumUI();
    ~NumUI();
    /// <summary>
    /// 数字を描画したい時用
    /// </summary>
    /// <param name="x">一番右端</param>
    /// <param name="y">Y座標</param>
    /// <param name="num">数字</param>
    /// <param name="scale">文字の大きさ</param>
    /// <returns>左端の座標</returns>
    int Draw(int x, int y, int num,float scale);
    /// <summary>
    /// 小数点も描画したい時用
    /// </summary>
    /// <param name="x">一番右端</param>
    /// <param name="y">Y座標</param>
    /// <param name="num">数字</param>
    /// <param name="scale">文字の大きさ</param>
    /// <returns>左端の座標</returns>
    int Draw(int x, int y, float num,float scale);
    /// <summary>
    /// 一文字の大きさ
    /// </summary>
    /// <returns></returns>
    int GetNumWidthSize();
private:
    //数字のデータ
    UIData numData;
    //小数点の画像
    UIData pointData;
};