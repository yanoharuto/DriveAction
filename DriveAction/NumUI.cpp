#include "NumUI.h"
#include "DxLib.h"
#include "Utility.h"
#include "OriginalMath.h"

NumUI::NumUI()
{
    numData = UIManager::CreateUIData(num);
    pointData= UIManager::CreateUIData(point);
}

NumUI::~NumUI()
{
}

/// <summary>
/// ������`�悵�������p
/// </summary>
/// <param name="x">��ԉE�[</param>
/// <param name="y">Y���W</param>
/// <param name="num">����</param>
/// <param name="scale">�����̑傫��</param>
/// <returns>���[�̍��W</returns>
int NumUI::Draw(int x, int y, int num,float scale)
{
    //����
    int digits = static_cast<int>(OriginalMath::GetDigits(num));
    //�\���ʒu���E�[�ɂ�������ړ�
    x -= static_cast<int> (scale * numData.width * digits);
    //�������[���ɂȂ�܂ŕ`�悷��@������`�悷��
    for (int i = digits; i > 0; i--)
    {
        //10�̂����Ŋ��������̂��܂�
        int drawNum = num / pow(TIMER_FONT_NUM, i - 1);
        //�`��
        int result = DrawRotaGraph(x, y, scale, 0, numData.dataHandle[drawNum], true);
        //�ʒu�����炷
        x += static_cast<int> (scale * numData.width);
        //���ɕ`�悵���������̏���
        num -= drawNum * pow(TIMER_FONT_NUM, i - 1);
    }
    return x;
}
/// <summary>
/// �����_���`�悵�������p
/// </summary>
/// <param name="x">��ԉE�[</param>
/// <param name="y">Y���W</param>
/// <param name="num">����</param>
/// <param name="scale">�����̑傫��</param>
/// <returns>���[�̍��W</returns>
int NumUI::Draw(int x, int y, float num, float scale)
{
    //��������
    int iNum = static_cast<int>(num);
    //�������ʂ̕���
    int decimalNum1 = (num - iNum) * 10;
    //������������
    int decimalNum2 = ((num - iNum) * 100 - decimalNum1 * 10);
    //�`��I�������ꏊ��edge�ɓn��
    int edge = Draw(x, y, decimalNum2, scale);
    edge -= static_cast<int> (scale * numData.width);
    edge = Draw(edge, y, decimalNum1, scale);
    edge -= static_cast<int> (scale * numData.width);
    //����������`��
    Draw(edge, y, iNum, scale);
    edge -= static_cast<int> (scale * numData.width);
    //�����_
    DrawRotaGraph(edge, y, pointData.size, 0, pointData.dataHandle[0], true);
    return x;
}
/// <summary>
/// �ꕶ���̑傫��
/// </summary>
/// <returns></returns>
int NumUI::GetNumWidthSize()
{
    return numData.width;
}
