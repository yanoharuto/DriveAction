#pragma once
#include "UIDataStruct.h"
#include <string>
class UI
{
public:
    UI() {};
    virtual ~UI() {};
    virtual void DrawUI() {};
    virtual void Update(std::string updateString) {};
};