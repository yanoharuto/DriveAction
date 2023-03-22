#include "UserInput.h"

static InputState aButtonState;
static InputState bButtonState;
static InputState keyInputState[KEY_INPUT_KIND_NUM];
static StickValueStruct stickValue;

UserInput::UserInput()
{
    keyInputCode[KeyInputKind::Up] = PAD_INPUT_UP;
    keyInputCode[KeyInputKind::Down] = PAD_INPUT_DOWN;
    keyInputCode[KeyInputKind::Left] = PAD_INPUT_LEFT;
    keyInputCode[KeyInputKind::Right] = PAD_INPUT_RIGHT;
    keyInputCode[KeyInputKind::Space] = PAD_INPUT_10;
}

void UserInput::Update()
{
    XINPUT_STATE input;
    GetJoypadXInputState(DX_INPUT_KEY_PAD1, &input);
    ButtonUpdate(input.Buttons[aButtonNum] != 0, aButtonState);
    ButtonUpdate(input.Buttons[aButtonNum] != 0, bButtonState);
    int inputKey = GetJoypadInputState(DX_INPUT_KEY);
    for (int i = 0; i < KEY_INPUT_KIND_NUM; i++)
    {
        ButtonUpdate(inputKey & keyInputCode[i], keyInputState[i]);
    }
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

InputState UserInput::GetInputState(KeyInputKind inputKind)
{
    return keyInputState[inputKind];
}

StickValueStruct UserInput::GetStickValue()
{
    return stickValue;
}



void UserInput::ButtonUpdate(bool inputJudge, InputState& _Button)
{    
    //ƒ{ƒ^ƒ“‚ª‰Ÿ‚³‚ê‚Ä‚½‚ç
    if (inputJudge)
    {
        //¡‰Ÿ‚³‚ê‚½‚©‰Ÿ‚µ‚Á‚Ï‚©
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
        //‰Ÿ‚µ‚Ä‚©‚ç—£‚µ‚½‚©A‰Ÿ‚³‚ê‚Ä‚¢‚È‚¢‚©
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