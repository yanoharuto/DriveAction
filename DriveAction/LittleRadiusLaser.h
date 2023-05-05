#pragma once
#include "RotatingLasers.h"
class LittleRadiusLaser :
    public RotatingLasers
{
public:
    LittleRadiusLaser(ObjectObserver* observer);
    ~LittleRadiusLaser();
    void Update()override;
private:
    static const float rotaSpeed;
    static const InitParam initParam;
};

