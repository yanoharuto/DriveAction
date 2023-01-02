#include "ImgUI.h"
#include "DxLib.h"

ImgUI::ImgUI()
{
    imgData = {};
}

ImgUI::ImgUI(UIData data)
{
    imgData = data;
}
ImgUI::~ImgUI()
{
    DeleteGraph(imgData.dataHandle);
}

void ImgUI::DrawUI()
{
    DrawRotaGraph(imgData.x, imgData.y, 0, 0, imgData.dataHandle, false, 0, 0);
}
