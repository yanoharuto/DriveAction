#include "ImgUI.h"
#include "DxLib.h"

ImgUI::ImgUI()
{
    imgData = {};
}

ImgUI::ImgUI(float size,UIData data)
{
    imgData = data;
    rate = size;
}
ImgUI::~ImgUI()
{
    DeleteGraph(imgData.dataHandle);
}

void ImgUI::DrawUI()
{
    DrawRotaGraph(imgData.x, imgData.y, rate, 0, imgData.dataHandle, true, 0, 0);
}
