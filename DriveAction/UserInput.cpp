#include "UserInput.h"

UserInput::UserInput()
    :aButtonState(InputState::Detach),
    bButtonState(InputState::Detach),
    stickValue({})
    
{
}

void UserInput::Update()
{

    XINPUT_STATE input;
    GetJoypadXInputState(DX_INPUT_PAD1, &input);
    ButtonUpdate(input, aButtonNum, aButtonState);
    ButtonUpdate(input, bButtonNum, bButtonState);
    StickUpdate(input);
}

InputState UserInput::GetInputAState()
{
    return aButtonState;
}

InputState UserInput::GetInputBState()
{
    return bButtonState;
}

StickValueStruct UserInput::GetStickValue()
{
    return stickValue;
}



void UserInput::ButtonUpdate(XINPUT_STATE _Input, int _Num, InputState& _Button)
{    
    //É{É^ÉìÇ™âüÇ≥ÇÍÇƒÇΩÇÁ
    if (_Input.Buttons[_Num] != 0)
    {
        //ç°âüÇ≥ÇÍÇΩÇ©âüÇµÇ¡ÇœÇ©
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
        //âüÇµÇƒÇ©ÇÁó£ÇµÇΩÇ©ÅAâüÇ≥ÇÍÇƒÇ¢Ç»Ç¢Ç©
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

    stickValue.LStickValueX = _Input.ThumbLX;
    stickValue.LStickValueY = _Input.ThumbLY;
    stickValue.RStickValueX = _Input.ThumbRX;
    stickValue.RStickValueY = _Input.ThumbRY;
}