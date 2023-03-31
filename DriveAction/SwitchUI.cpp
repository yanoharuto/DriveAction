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
    spaceKeyUI.dataHandle = CreateFontToHandle("BIZ UDゴシック", bigPleaseSpaceKeySize, 3, DX_FONTTYPE_NORMAL);
    smallUI = new StringUI(smalleUIColor, spaceKeyUI, pleaseSpaceKeyUIString);


    x += bigPleaseSpaceKeySize - smallPleaseSpaceKeySize;
    spaceKeyUI.dataHandle = CreateFontToHandle("BIZ UDゴシック", smallPleaseSpaceKeySize, 3, DX_FONTTYPE_NORMAL);
    bigUI = new StringUI(bigUIColor, spaceKeyUI, pleaseSpaceKeyUIString);

}

SwitchUI::~SwitchUI()
{
    SAFE_DELETE(bigUI);
    SAFE_DELETE(smallUI);
}

void SwitchUI::Update()
{
    time += DELTATIME;
    
}

void SwitchUI::Draw()
{
    if ((int)time % 2 == 1)
    {
        bigUI->DrawRightAlignedString();
    }
    else
    {
        smallUI->DrawRightAlignedString();
    }
}
