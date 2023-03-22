#include "ModelUpdater.h"

ModelUpdater::ModelUpdater()
{
    modelHandle = -1;
}

ModelUpdater::ModelUpdater(int setModelHandle)
{
    modelHandle = setModelHandle;
}

ModelUpdater::~ModelUpdater()
{
    MV1DeleteModel(modelHandle);
}

void ModelUpdater::ModelSetMatrix(ItemArgumentCarInfo objInfo)
{
    // �����ɍ��킹�ĉ�].
    MV1SetRotationZYAxis(modelHandle,objInfo.direction, VGet(0.0f, 1.0f, 0.0f), 0.0f);

    // ���f���Ɍ����Ăق��������ɉ�].
    MATRIX tmpMat = MV1GetMatrix(modelHandle);
    MATRIX rotYMat = MGetRotY(180.0f * RAGE);
    tmpMat = MMult(tmpMat, rotYMat);
    MV1SetRotationMatrix(modelHandle, tmpMat);
}

void ModelUpdater::UpdateMV1Pos(VECTOR position)
{
    // �RD���f���̃|�W�V�����ݒ�
    MV1SetPosition(modelHandle, position);
}

void ModelUpdater::SetScale(VECTOR scale)
{
    MV1SetScale(modelHandle, scale);
}
