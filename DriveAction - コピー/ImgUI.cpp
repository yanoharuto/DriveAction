#include "ImgUI.h"
#include "DxLib.h"

ImgUI::ImgUI()
{
    uiData = {};
}

ImgUI::ImgUI(float size,UIData data)
    :UI(data)
{
    rate = size;
}
ImgUI::~ImgUI()
{
    DeleteGraph(uiData.dataHandle);
}

void ImgUI::DrawUI()
{

    DrawRotaGraph(uiData.x, uiData.y, rate, 0, uiData.dataHandle, true, 0, 0);
}

