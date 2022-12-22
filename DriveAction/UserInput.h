#pragma once
#include "DxLib.h"
/// <summary>
/// ボタンの入力状況
/// </summary>
enum InputState
{
    Free,
    Push,
    Hold,
    Detach
};

struct StickValueStruct
{
    short LStickValueX;
    short LStickValueY;
    short RStickValueX;
    short RStickValueY;
};
class UserInput
{
public:
    UserInput();
    ~UserInput() {};
    /// <summary>
    /// 入力状況更新
    /// </summary>
    void Update();
    /// <summary>
    /// Aボタンの入力状況所得
    /// </summary>
    InputState GetInputAState();
    /// <summary>
    /// Bボタンの入力状況所得
    /// </summary>
    InputState GetInputBState();
    /// <summary>
    /// スティックの入力状況所得
    /// </summary>
    StickValueStruct GetStickValue();
private:
    /// <summary>
    /// ボタンの入力更新
    /// </summary>
    /// <param name="_Input">入力状況</param>
    /// <param name="_Num">ボタンの割り当て番号</param>
    /// <param name="_Button">更新したいボタン</param>
    void ButtonUpdate(XINPUT_STATE _Input,int _Num,InputState &_Button);
    /// <summary>
    /// Stickの入力更新
    /// </summary>
    /// <param name="_Input"></param>
    void StickUpdate(XINPUT_STATE _Input);
    InputState aButtonState;
    InputState bButtonState;
    StickValueStruct stickValue;
    //Aボタンの割り当て番号
    const int aButtonNum = 12;
    //Bボタンの割り当て番号
    const int bButtonNum = 13;
};

