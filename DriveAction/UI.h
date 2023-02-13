#pragma once
#include "UIDataStruct.h"
#include <string>
/// <summary>
/// UI
/// </summary>
class UI abstract
{
public:
    UI() { uiData = {}; };
    /// <summary>
    /// ‚Ç‚ÌˆÊ’u‚É•`‰æ‚·‚é‚©‚Æ‚©•`‰æ‚µ‚½‚¢‚à‚Ì‚Æ‚©“n‚µ‚Ä—~‚µ‚¢
    /// </summary>
    /// <param name="data"></param>
    UI(UIData data) { uiData = data; };
    virtual ~UI() {};
    /// <summary>
    /// •`‰æ
    /// </summary>
    virtual void DrawUI() {};
    /// <summary>
    /// ˆÊ’u•ÏX
    /// </summary>
    /// <param name="x"></param>
    /// <param name="y"></param>
    void SetXY(int x, int y) { uiData.x = x; uiData.y = y; };
protected:
    //•`‰æêŠ‚Æ•`‰æ‘ÎÛ‚Ìƒf[ƒ^
    UIData uiData;
};