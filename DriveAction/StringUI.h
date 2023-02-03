#pragma once
#include <string>
#include "UIDataStruct.h"
#include "UI.h"
struct UIStringData;
/// <summary>
/// ������`�悷��
/// </summary>
class StringUI:public UI
{
public:
    StringUI();
    /// <summary>
    /// �ǂ̈ʒu�łǂ������t�H�[�}�b�g���ǂ������F���n����
    /// </summary>
    /// <param name="colorValue"></param>
    /// <param name="data"></param>
    StringUI(unsigned int colorValue, UIData data);
    /// <summary>
    /// �ǂ̈ʒu�łǂ������t�H�[�}�b�g���ǂ������F�����������ė~�������n����
    /// </summary>
    /// <param name="colorValue"></param>
    /// <param name="data"></param>
    /// <param name="str"></param>
    StringUI(unsigned int colorValue, UIData data, std::string str);
    ~StringUI();
    /// <summary>
    /// �E�l�ߕ�����`��
    /// </summary>
    void DrawRightAlignedString();
    /// <summary>
    /// ���l�ߕ�����`��
    /// </summary>
    void DrawLeftAlignedString();
    /// <summary>
    /// �`�悷�镶����X�V
    /// </summary>
    /// <param name="updateString"></param>
    void UpdateString(std::string updateString);
private:
    //�`�悷�镶����̐F
    unsigned int color;
    //�`�悷�镶����
    std::string string;

};

