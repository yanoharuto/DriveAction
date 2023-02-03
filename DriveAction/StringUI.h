#pragma once
#include <string>
#include "UIDataStruct.h"
#include "UI.h"
struct UIStringData;
/// <summary>
/// 文字を描画する
/// </summary>
class StringUI:public UI
{
public:
    StringUI();
    /// <summary>
    /// どの位置でどういうフォーマットかどういう色か渡して
    /// </summary>
    /// <param name="colorValue"></param>
    /// <param name="data"></param>
    StringUI(unsigned int colorValue, UIData data);
    /// <summary>
    /// どの位置でどういうフォーマットかどういう色か何を書いて欲しいか渡して
    /// </summary>
    /// <param name="colorValue"></param>
    /// <param name="data"></param>
    /// <param name="str"></param>
    StringUI(unsigned int colorValue, UIData data, std::string str);
    ~StringUI();
    /// <summary>
    /// 右詰め文字列描画
    /// </summary>
    void DrawRightAlignedString();
    /// <summary>
    /// 左詰め文字列描画
    /// </summary>
    void DrawLeftAlignedString();
    /// <summary>
    /// 描画する文字列更新
    /// </summary>
    /// <param name="updateString"></param>
    void UpdateString(std::string updateString);
private:
    //描画する文字列の色
    unsigned int color;
    //描画する文字列
    std::string string;

};

