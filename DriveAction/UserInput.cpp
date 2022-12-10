#include "UserInput.h"

UserInput::UserInput()
    :AButtonState(InputState::Detach),
    BButtonState(InputState::Detach),
    StickValue({})
    
{
}

void UserInput::Update()
{

    XINPUT_STATE input;
    GetJoypadXInputState(DX_INPUT_PAD1, &input);
    ButtonUpdate(input, AButtonNum, AButtonState);
    ButtonUpdate(input, BButtonNum, BButtonState);
    StickUpdate(input);
}

InputState UserInput::GetInputAState()
{
    return AButtonState;
}

InputState UserInput::GetInputBState()
{
    return BButtonState;
}

StickValueStruct UserInput::GetStickValue()
{
    return StickValue;
}



void UserInput::ButtonUpdate(XINPUT_STATE _Input, int _Num, InputState& _Button)
{    
    //�{�^����������Ă���
    if (_Input.Buttons[_Num] != 0)
    {
        //�������ꂽ���������ς�
        switch (_Button)
        {
        default:
            _Button = InputState::Free;
            break;
        case InputState::Free:
            _Button = InputState::Push;
            break;
        case InputState::Push:
            _Button = InputState::Hold;
            break;
        case InputState::Hold:
            _Button = InputState::Hold;
            break;
        }
    }
    else
    {
        //�����Ă��痣�������A������Ă��Ȃ���
        switch (_Button)
        {
        default:
            _Button = InputState::Free;
            break;
        case InputState::Detach:
            _Button = InputState::Free;
            break;
        case InputState::Push:
            _Button = InputState::Detach;
            break;
        case InputState::Hold:
            _Button = InputState::Detach;
            break;
        }
    }
}

void UserInput::StickUpdate(XINPUT_STATE _Input)
{

    StickValue.LStickValueX = _Input.ThumbLX;
    StickValue.LStickValueY = _Input.ThumbLY;
    StickValue.RStickValueX = _Input.ThumbRX;
    StickValue.RStickValueY = _Input.ThumbRY;
}