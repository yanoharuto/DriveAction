#include "FlyShipInitializer.h"
#include "BomberFlyShip.h"
#include "FiringItemManager.h"
#include "LaserFlyShip.h"
#include "CourceDataLoader.h"
#include "OriginalMath.h"
#include "Utility.h"
FlyShipInitializer::FlyShipInitializer()
{
    ufoPosList = CourceDataLoader::GetVECTORData(ufoPosPass);
}

FlyShipInitializer::~FlyShipInitializer()
{
}

void FlyShipInitializer::IntFlyShip(FlyShipKind shipKind, PlayerRelatedInfo playerInfo, FlyShip* flyship)
{
    //出現場所
    VECTOR generatePos = {};
    //目標地点
    VECTOR destinationPos = {};
    VECTOR dir = {};
    FlyShip* obj = nullptr;
    switch (shipKind)
    {
    case Bomber:
        dir = VScale(VGet(OriginalMath::GetRandom(-1, 1), 0, OriginalMath::GetRandom(-1, 1)), 100.0f);
        generatePos = VAdd(playerInfo.objInfo.pos, dir);
        destinationPos = VAdd(playerInfo.objInfo.pos, VScale(playerInfo.objInfo.dir, 100.0f));
        dir = VScale(VCross(VNorm(VSub(generatePos, destinationPos)), VGet(0, 1, 0)), 50.0f);
        for (int i = 0; i < 3; i++)
        {
            obj = new BomberFlyShip(generatePos, destinationPos);
            generatePos = VAdd(generatePos, dir);
        }
        break;
    case UFO:

        dir = VGet(1.0f, 0.0f, 0.0f);
        for (int i = 0; i < 6; i++)
        {
            generatePos = VAdd(destinationPos, VScale(dir, 200.0f));
            obj = new LaserFlyShip(generatePos, destinationPos);
            dir = VNorm(OriginalMath::GetYRotateVector(dir, 60.0f));
        }

        break;
    }
}