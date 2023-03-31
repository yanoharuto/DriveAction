#include "Rocket.h"
#include "EffectManager.h"
#include "AssetManager.h"
#include "EffekseerForDXLib.h"
#include "ConflictManager.h"
#include "Utility.h"
//ロケットのモデルのアドレス
 const std::string Rocket::rocketModelPass = "Item/Rocket/Rocket04_Grey.mv1";
//エフェクトのmodelのアドレス
 const std::string Rocket::effectPass = "bomb.efkefc";
//落下速度
 const float Rocket::setFallingSpeed = 0.7f;
//はじき返す力
 const float Rocket::setBouncePower = 4.25f;
//重力
 const float Rocket::gravityPower = 0.08f;
//ロケットのサイズ
 const float Rocket::setModelSize = 3.5f;
//エフェクトのサイズ
 const float Rocket::setEffectSize = 22.000f;
//当たり判定の大きさ
 const float Rocket::setRadius = 25.0f;
 //燃えた時の当たり判定の大きさ
 const float Rocket::setBurnRadius = 42.0f;
 
/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="carInfo"></param>
Rocket::Rocket(ItemArgumentCarInfo carInfo)
{
    modelHandle = MV1DuplicateModel(AssetManager::GetDuplicate3DModelAssetHandle(rocketModelPass));
    MV1SetScale(modelHandle, VGet(setModelSize, setModelSize, setModelSize));
    fallingSpeed = setFallingSpeed;
    tag = ObjectTag::damageObject;
    radius = setRadius;
    position = carInfo.position;
    position = VAdd(position, VScale(VGet(0, -1, 0), carInfo.radius + radius));
    EffectManager::LoadEffectManager(effectPass, setEffectSize);
    velocity = VGet(0, 0, 0);
    direction = VGet(1, 0, 0);
    onGround = false;
    collider = new SphereCollider(this);
}

Rocket::~Rocket()
{
    StopEffekseer3DEffect(burnEffect);
    ConflictManager::EraceConflictObjInfo(collider);
    SAFE_DELETE(collider);
}
/// <summary>
/// 更新
/// </summary>
/// <param name="deltaTime"></param>
void Rocket::Update()
{
    //地面にぶつかる前は落ちていく
    if (!onGround)
    {
        position.y -= fallingSpeed;
        fallingSpeed += fallingSpeed * gravityPower;
        //地面にぶつかりそうになかったらエフェクトを出す
        if (position.y < 0.0f)
        {
            if (burnEffect == -1)
            {
                burnEffect = EffectManager::GetPlayEffect3D(effectPass);
                float positionY = position.y - radius;
                SetPosPlayingEffekseer3DEffect(burnEffect, position.x, positionY, position.z);
                radius = setBurnRadius;
                onGround = true;
            }
        }
    }
    else
    {
        //エフェクトを描画し終わったら終了
        if (IsEffekseer3DEffectPlaying(burnEffect) == -1)
        {
            aliveFlag = false;
            burnEffect = -1;
        }
    }
}
/// <summary>
/// 衝突後の処理
/// </summary>
void Rocket::ConflictProccess(ConflictExamineResultInfo resultInfo)
{
    if (resultInfo.tag != ObjectTag::damageObject)
    {
        if (burnEffect==-1)
        {
            //ダメージ判定のあるオブジェクト以外に衝突後エフェクトを出す
            burnEffect = EffectManager::GetPlayEffect3D(effectPass);
            float positionY = position.y - radius;
            SetPosPlayingEffekseer3DEffect(burnEffect, position.x, positionY, position.z);
            //当たり判定を爆発と同じくらいにする
            radius = setBurnRadius;
            onGround = true;
        }
    }
}