#pragma once
#include "DxLib.h"
/// <summary>
/// �{�^���̓��͏�
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
    /// ���͏󋵍X�V
    /// </summary>
    void Update();
    /// <summary>
    /// A�{�^���̓��͏󋵏���
    /// </summary>
    InputState GetInputAState();
    /// <summary>
    /// B�{�^���̓��͏󋵏���
    /// </summary>
    InputState GetInputBState();
    /// <summary>
    /// �X�e�B�b�N�̓��͏󋵏���
    /// </summary>
    StickValueStruct GetStickValue();
private:
    /// <summary>
    /// �{�^���̓��͍X�V
    /// </summary>
    /// <param name="_Input">���͏�</param>
    /// <param name="_Num">�{�^���̊��蓖�Ĕԍ�</param>
    /// <param name="_Button">�X�V�������{�^��</param>
    void ButtonUpdate(XINPUT_STATE _Input,int _Num,InputState &_Button);
    /// <summary>
    /// Stick�̓��͍X�V
    /// </summary>
    /// <param name="_Input"></param>
    void StickUpdate(XINPUT_STATE _Input);
    InputState aButtonState;
    InputState bButtonState;
    StickValueStruct stickValue;
    //A�{�^���̊��蓖�Ĕԍ�
    const int aButtonNum = 12;
    //B�{�^���̊��蓖�Ĕԍ�
    const int bButtonNum = 13;
};

