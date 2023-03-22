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
enum KeyInputKind
{
    Up = 0,
    Down = 1,
    Left = 2,
    Right = 3,
    Space = 4,
};
#define KEY_INPUT_KIND_NUM 5
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
    static InputState GetInputAState();
    /// <summary>
    /// Bボタンの入力状況所得
    /// </summary>
    static InputState GetInputBState();
    static InputState GetInputState(KeyInputKind inputKind);
    /// <summary>
    /// スティックの入力状況所得
    /// </summary>
    static StickValueStruct GetStickValue();
private:
    /// <summary>
    /// ボタンの入力更新
    /// </summary>
    /// <param name="_Input">入力状況</param>
    /// <param name="_Num">ボタンの割り当て番号</param>
    /// <param name="_Button">更新したいボタン</param>
    void ButtonUpdate(bool inputJudge,InputState &_Button);
    /// <summary>
    /// Stickの入力更新
    /// </summary>
    /// <param name="_Input"></param>
    void StickUpdate(XINPUT_STATE _Input);

    //Aボタンの割り当て番号
    const int aButtonNum = 12;
    //Bボタンの割り当て番号
    const int bButtonNum = 13;
    int keyInputCode[KEY_INPUT_KIND_NUM];
};

