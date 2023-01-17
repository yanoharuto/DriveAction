#include "SwitchUI.h"
#include "Utility.h"
SwitchUI::SwitchUI()
{
    x = SCREEN_WIDTH;
    x /= 2;
    x -= 200;
    y = SCREEN_HEIGHT;
    y /= 8;
    y *= 7;
    UIData spaceKeyUI;
    spaceKeyUI.x = x - 50;
    spaceKeyUI.y = y;
    spaceKeyUI.dataHandle = CreateFontToHandle("BIZ UD�S�V�b�N", bigPleaseSpaceKeySize, 3, DX_FONTTYPE_NORMAL);
    smallUI = new StringUI(smallPleaseSpaceKeyUIColor, spaceKeyUI, pleaseSpaceKeyUIString);


    x += bigPleaseSpaceKeySize - smallPleaseSpaceKeySize;
    spaceKeyUI.dataHandle = CreateFontToHandle("BIZ UD�S�V�b�N", smallPleaseSpaceKeySize, 3, DX_FONTTYPE_NORMAL);
    bigUI = new StringUI(bigPleaseSpaceKeyUIColor, spaceKeyUI, pleaseSpaceKeyUIString);

}

SwitchUI::~SwitchUI()
{
    SAFE_DELETE(bigUI);
    SAFE_DELETE(smallUI);
}

void SwitchUI::Update(float deltaTime)
{
    time += deltaTime;
    if ((int)time % 2 == 1)
    {
        bigUI->StopDrawUI(false);
        smallUI->StopDrawUI(true);
    }
    else
    {
        bigUI->StopDrawUI(true);
        smallUI->StopDrawUI(false);
    }
}

void SwitchUI::Draw()
{
    bigUI->DrawUI();
    smallUI->DrawUI();
}