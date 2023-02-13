#include "Kite.h"
#include "AssetManager.h"
#include "OriginalMath.h"
#include "DamageObjectGenerator.h"
Kite::Kite()
{
	effecacyTime = setEffecacyTime;
	itemTag = kite;
	modelHandle = AssetManager::Get3DModelAssetHandle(modelAddress);
	leftRocketModelHandle = AssetManager::Get3DModelAssetHandle(modelAddress);
	MV1SetScale(modelHandle, VGet(0.1f, 0.1f, 0.1f));
	MV1SetScale(leftRocketModelHandle, VGet(0.1f, 0.1f, 0.1f));
}

Kite::~Kite()
{
	MV1DeleteModel(modelHandle);
}

void Kite::Update(float deltaTime, ItemArgumentCarInfo carInfo)
{
	if (useSituation == ItemUseSituation::Useing)
	{
		//���ʎ��Ԍ���
 		effecacyTime -= deltaTime;
		//�g���؂�����
		if (effecacyTime < 0)
		{
			useSituation = ItemUseSituation::DoneUsing;
		}
		else
		{
			VECTOR addPos = VScale(VCross(carInfo.direction, VGet(0, 1, 0)), carInfo.radius);
			SetMatrix(modelHandle,carInfo,addPos);
			addPos = VScale(VCross(VGet(0, 1, 0), carInfo.direction), carInfo.radius);
			SetMatrix(leftRocketModelHandle,carInfo, addPos);	
			//�N�[���^�C�����I������
			if (coolTime < -0.1f)
			{
				coolTime = setCoolTime;
			}
			else
			{
				coolTime -= deltaTime;
			}
			//���ʗʂ̍X�V
			effecacyValue = effecacyValue < maxHeight ? effecacyValue + flyPower * deltaTime : maxHeight;
		}
	}
}

void Kite::Draw()
{
	MV1DrawModel(modelHandle);
	MV1DrawModel(leftRocketModelHandle);
}
/// <summary>
/// ���e�𗎂Ƃ���
/// </summary>
/// <param name="carInfo"></param>
void Kite::ShowEffect(ItemArgumentCarInfo carInfo)
{
	if (useSituation != ItemUseSituation::DoneUsing)
	{
		useSituation = ItemUseSituation::Useing;
	}
	if (useSituation == ItemUseSituation::Useing && coolTime < 0)
	{
		DamageObjectGenerator::GenerateDamageObject(itemTag, carInfo);
		coolTime = setCoolTime;
	}
}

void Kite::SetMatrix(int modelH, ItemArgumentCarInfo carInfo, VECTOR addPos)
{
	// �����ɍ��킹�ĉ�].
	MV1SetRotationZYAxis(modelH, carInfo.direction, VGet(0.0f, 1.0f, 0.0f), 0.0f);
	// ���f���Ɍ����Ăق��������ɉ�].
	MATRIX tmpMat = MV1GetMatrix(modelH);
	MATRIX rotYMat = MGetRotY((180.0f) * RAGE);
	tmpMat = MMult(tmpMat, rotYMat);
	MV1SetRotationMatrix(modelH, tmpMat);
	MV1SetPosition(modelH, VAdd(addPos, carInfo.position));
}
